#include "TestResults.h"
#include "TestReporter.h"
#include "TimeHelpers.h"

namespace UnitTest
{

TestResults::TestResults(TestReporter* testReporter)
    : m_testReporter(testReporter)
    , m_failure(false)
    , m_startTime(0)
    , m_endTime(0)
{
    m_startTime = TimeHelpers::GetTimeInMs();
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

void TestResults::TestsCompleted()
{
    m_endTime = TimeHelpers::GetTimeInMs();
}

bool TestResults::Failed() const
{
    return m_failure;
}

float TestResults::GetTimeElapsed() const
{
    return (m_endTime - m_startTime)/(float)1000;
}

}

