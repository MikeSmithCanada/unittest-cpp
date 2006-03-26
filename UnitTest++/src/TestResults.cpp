#include "TestResults.h"
#include "TestReporter.h"

namespace UnitTest {

TestResults::TestResults(TestReporter* testReporter)
    : m_testReporter(testReporter)
    , m_testCount(0)
    , m_failureCount(0)
{
}

void TestResults::OnTestStart(char const* testName)
{
    ++m_testCount;
    if (m_testReporter)
        m_testReporter->ReportTestStart(testName);
}

void TestResults::OnTestFailure(char const* file, int const line, 
        char const* testName, char const* failure)
{
    ++m_failureCount;
    if (m_testReporter)
        m_testReporter->ReportFailure(file, line, testName, failure);
}

void TestResults::OnTestFinish(char const* testName, float secondsElapsed)
{
    if (m_testReporter)
        m_testReporter->ReportTestFinish(testName, secondsElapsed);
}


int TestResults::GetTestCount() const
{
    return m_testCount;
}

int TestResults::GetFailureCount() const
{
    return m_failureCount;
}


}

