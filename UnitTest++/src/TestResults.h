#ifndef UNITTEST_TESTRESULTS_H
#define UNITTEST_TESTRESULTS_H

namespace UnitTest
{

class TestReporter;

class TestResults
{
public:
    explicit TestResults(TestReporter* reporter = 0);

    void ReportFailure(char const* file, int line, char const* testName, char const* failure);
    void ReportDone(char const* testName);
    void TestsCompleted();

    bool Failed() const;

private:
    TestReporter* m_testReporter;
    bool m_failure;

    // revoked
    TestResults(TestResults const&);
    TestResults& operator =(TestResults const&);
};

}

#endif

