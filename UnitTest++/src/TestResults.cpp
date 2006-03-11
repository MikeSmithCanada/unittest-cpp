#include "TestResults.h"
#include "TestReporter.h"

namespace UnitTest
{

TestResults::TestResults(TestReporter* testReporter)
    : m_testReporter(testReporter)
    , m_failure(false)
{
}

void TestResults::ReportFailure(char const* file, int const line, 
        char const* testName, char const* failure)
{
    m_failure = true;
    if (m_testReporter)
        m_testReporter->ReportFailure(file, line, testName, failure);
}

void TestResults::ReportDone(const std::string& testName)
{
    if (m_testReporter)
        m_testReporter->ReportSingleResult(testName, m_failure);
}

bool TestResults::Failed() const
{
    return m_failure;
}

}

