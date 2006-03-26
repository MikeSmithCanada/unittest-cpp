#ifndef UNITTEST_TESTREPORTERSTDOUT_H
#define UNITTEST_TESTREPORTERSTDOUT_H

#include "TestReporter.h"

namespace UnitTest {

class TestReporterStdout : public TestReporter
{
private:
    virtual void ReportTestStart(char const* testName);
    virtual void ReportFailure(char const* file, int line, char const* testName, char const* failure);
    virtual void ReportTestFinish(char const* testName, float secondsElapsed);
    virtual void ReportSummary(int testCount, int failureCount, float secondsElapsed);
};

}

#endif 

