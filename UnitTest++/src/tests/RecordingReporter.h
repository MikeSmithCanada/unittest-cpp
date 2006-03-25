#ifndef UNITTEST_RECORDINGREPORTER_H
#define UNITTEST_RECORDINGREPORTER_H

#include "../TestReporter.h"
#include <cstring>


struct RecordingReporter : public UnitTest::TestReporter
{
private:
    enum { kMaxStringLength = 256 };

public:
    RecordingReporter()
        : testRunCount(0)
        , testFailedCount(0)
        , lastFailedLine(0)
        , testFinishedCount(0)
        , lastFinishedTestTime(0)
        , summaryTestCount(0)
        , summaryFailureCount(0)
        , summarySecondsElapsed(0)
    {
    }

    virtual void ReportTestStart(char const* testName)
    {
        ++testRunCount;
        std::strcpy(lastStartedTest, testName);
    }

    virtual void ReportFailure(char const* file, int line, char const* testName, char const* failure)
    {
        ++testFailedCount;
        std::strcpy(lastFailedFile, file);
        lastFailedLine = line;
        std::strcpy(lastFailedTest, testName);
        std::strcpy(lastFailedMessage, failure);
    }

    virtual void ReportTestFinish(char const* testName, float testDuration)
    {
        ++testFinishedCount;
        std::strcpy(lastFinishedTest, testName);
        lastFinishedTestTime = testDuration;
    }

    virtual void ReportSummary(int testCount, int failureCount, float secondsElapsed) 
    {
        summaryTestCount = testCount;
        summaryFailureCount = failureCount;
        summarySecondsElapsed = secondsElapsed;
    }

    int testRunCount;
    char lastStartedTest[kMaxStringLength];

    int testFailedCount;
    char lastFailedFile[kMaxStringLength];
    int lastFailedLine;
    char lastFailedTest[kMaxStringLength];
    char lastFailedMessage[kMaxStringLength];

    int testFinishedCount;
    char lastFinishedTest[kMaxStringLength];
    float lastFinishedTestTime;

    int summaryTestCount;
    int summaryFailureCount;
    float summarySecondsElapsed;
};


#endif
