#ifndef UNITTEST_TESTREPORTER_H
#define UNITTEST_TESTREPORTER_H


namespace UnitTest
{

class TestReporter
{
public:
    virtual ~TestReporter();

    virtual void ReportFailure(char const* file, int line, char const* testName, char const* failure) = 0;
    virtual void ReportSingleResult(char const* testName, bool failed) = 0;
    virtual void ReportSummary(int testCount, int failureCount, float secondsElapsed) = 0;

protected:
    TestReporter();
};

}
#endif

