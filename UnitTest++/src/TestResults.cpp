#include "TestResults.h"
#include "TestReporter.h"

namespace UnitTest
{

TestResults::TestResults(TestReporter* testReporter)
    : m_testReporter(testReporter)
    , m_failure(false)
{
}

void TestResults::OnTestStart(char const* testName)
{
    if (m_testReporter)
        m_testReporter->ReportTestStart(testName);
}

void TestResults::OnTestFailure(char const* file, int const line, 
        char const* testName, char const* failure)
{
    m_failure = true;
    if (m_testReporter)
        m_testReporter->ReportFailure(file, line, testName, failure);
}

bool TestResults::Failed() const
{
    return m_failure;
}

}

