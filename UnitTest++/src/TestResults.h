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

    void ReportFailure(char const* file, int line, char const* testName, char const* failure);
    void ReportDone(const std::string& testName);
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

