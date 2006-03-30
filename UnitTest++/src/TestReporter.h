#ifndef UNITTEST_TESTREPORTER_H
#define UNITTEST_TESTREPORTER_H


namespace UnitTest {

class TestReporter
{
public:
    virtual ~TestReporter();

    virtual void ReportTestStart(char const* testName) = 0;
    virtual void ReportFailure(char const* file, int line, char const* testName, char const* failure) = 0;
    virtual void ReportTestFinish(char const* testName, float secondsElapsed) = 0;
    virtual void ReportSummary(int testCount, int failureCount, float secondsElapsed) = 0;
};

}
#endif

