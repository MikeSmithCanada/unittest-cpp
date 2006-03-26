#ifndef UNITTEST_TESTRESULTS_H
#define UNITTEST_TESTRESULTS_H

namespace UnitTest {

class TestReporter;

class TestResults
{
public:
    explicit TestResults(TestReporter* reporter = 0);

    void OnTestStart(char const* testName);
    void OnTestFailure(char const* file, int line, char const* testName, char const* failure);
    void OnTestFinish(char const* testName, float secondsElapsed);

    int GetTestCount() const;
    int GetFailureCount() const;

private:
    TestReporter* m_testReporter;
    int m_testCount;
    int m_failureCount;

    // revoked
    TestResults(TestResults const&);
    TestResults& operator =(TestResults const&);
};

}

#endif

