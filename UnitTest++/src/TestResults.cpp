#include "TestResults.h"
#include "TestReporter.h"

#include "TestDetails.h"

namespace UnitTest {

TestResults::TestResults(TestReporter* testReporter)
    : m_testReporter(testReporter)
    , m_testCount(0)
    , m_failureCount(0)
{
}

void TestResults::OnTestStart(TestDetails const& test)
{
    ++m_testCount;
    if (m_testReporter)
        m_testReporter->ReportTestStart(test);
}

void TestResults::OnTestFailure(TestDetails const& test, char const* failure)
{
    ++m_failureCount;
    if (m_testReporter)
        m_testReporter->ReportFailure(test, failure);
}

void TestResults::OnTestFinish(TestDetails const& test, float secondsElapsed)
{
    if (m_testReporter)
        m_testReporter->ReportTestFinish(test, secondsElapsed);
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
