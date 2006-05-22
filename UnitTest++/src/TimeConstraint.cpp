#include "TimeConstraint.h"
#include "TestResults.h"
#include "MemoryOutStream.h"

namespace UnitTest {


TimeConstraint::TimeConstraint(int ms, TestResults& result, char const* filename, int lineNumber,
                    TestDetails const& details)
    : m_result (result)
    , m_maxMs (ms)
    , m_filename (filename)
    , m_lineNumber (lineNumber)
    , m_details (details)
{
    m_timer.Start();
}

TimeConstraint::~TimeConstraint()
{
    int const totalTimeInMs = m_timer.GetTimeInMs();
    if (totalTimeInMs > m_maxMs)
    {
        MemoryOutStream stream;
        stream << "Time constraint failed. Expected to run test under " << m_maxMs <<
                  "ms but took " << totalTimeInMs << "ms.";
        m_result.OnTestFailure(m_details, m_filename, m_lineNumber, stream.GetText());
    }
}

}
