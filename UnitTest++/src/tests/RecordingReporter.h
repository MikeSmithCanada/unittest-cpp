#ifndef UNITTEST_RECORDINGREPORTER_H
#define UNITTEST_RECORDINGREPORTER_H

#include "../TestReporter.h"


struct RecordingReporter : public UnitTest::TestReporter
{
public:
    RecordingReporter()
        : testRunCount(0)        
        , lastReportedTest(0)
        , testFailedCount(0)
        , lastFailedFile(0)
        , lastFailedLine(0)
        , lastFailedTest(0)
        , lastFailedMessage(0)
        , summaryTestCount(0)
        , summaryFailureCount(0)
        , summarySecondsElapsed(0)
    {
    }
    
    virtual void ReportTestStart(char const* testName)
    {
        ++testRunCount;
        lastReportedTest = testName;
    }

    virtual void ReportFailure(char const* file, int line, char const* testName, char const* failure)
    {
        ++testFailedCount;
        lastFailedFile = file;
        lastFailedLine = line;
        lastFailedTest = testName;
        lastFailedMessage = failure;
    }

    virtual void ReportSummary(int testCount, int failureCount, float secondsElapsed) 
    {
        summaryTestCount = testCount;
        summaryFailureCount = failureCount;
        summarySecondsElapsed = secondsElapsed;
    }

    int testRunCount;    
    char const* lastReportedTest;
    
    int testFailedCount;
    char const* lastFailedFile;
    int lastFailedLine;
    char const* lastFailedTest;
    char const* lastFailedMessage;
    
    int summaryTestCount;
    int summaryFailureCount;
    float summarySecondsElapsed;
};


#endif
