#include "TimeConstraint.h"
#include "TestResults.h"
#include <cstdio>


namespace UnitTest {


TimeConstraint::TimeConstraint(int ms, TestResults& result, char const* filename, int lineNumber,
                    char const* testName)
    : m_result (result)
    , m_maxMs (ms)
    , m_filename (filename)
    , m_lineNumber (lineNumber)
    , m_testName (testName)
{
    m_timer.Start();
}


TimeConstraint::~TimeConstraint()
{
    int const totalTimeInMs = m_timer.GetTimeInMs();
    if (totalTimeInMs > m_maxMs)
    {
        char txt[256];
        std::sprintf (txt, "Time constraint failed. Expected to run test under %i ms but took %i ms.",
            m_maxMs, totalTimeInMs);
        m_result.OnTestFailure(m_filename, m_lineNumber, m_testName, txt);
    }
}

}
