#ifndef TEST_RESULTS_H
#define TEST_RESULTS_H

#include <string>

namespace UnitTest
{

class TestReporter;

class TestResults
{
public:
    explicit TestResults(TestReporter* reporter = 0);

    void ReportFailure(char const* file, int line, const char* testName, std::string failure);
    void ReportDone(const std::string& testName);
    void TestsCompleted();

    bool Failed() const;
    float GetTimeElapsed() const;

private:
    TestReporter* m_testReporter;
    bool m_failure;
    int m_startTime;
    int m_endTime;

    // revoked
    TestResults(TestResults const&);
    TestResults& operator =(TestResults const&);
};

}

#endif

