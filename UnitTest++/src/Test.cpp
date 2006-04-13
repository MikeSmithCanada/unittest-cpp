#include "Config.h"
#include "Test.h"
#include "TestResults.h"
#include "AssertException.h"
#include "MemoryOutStream.h"
#ifdef UNITTEST_POSIX
    #include "Posix/SignalTranslator.h"
#endif


namespace UnitTest {

TestList& Test::GetTestList()
{
    static TestList s_list;
    return s_list;
}

Test::Test(char const* testName, char const* filename, int const lineNumber)
    : next(0)
    , m_testName(testName)
    , m_filename(filename)
    , m_lineNumber(lineNumber)
    , m_timeConstraintExempt(false)
{
}

Test::~Test()
{
}

void Test::Run(TestResults& testResults) const
{
    try
    {
#ifdef UNITTEST_POSIX
        UNITTEST_THROW_SIGNALS
#endif
        RunImpl(testResults);
    }
    catch (AssertException const& e)
    {
        testResults.OnTestFailure(e.Filename(), e.LineNumber(), m_testName, e.what());
    }
    catch (std::exception const& e)
    {
        MemoryOutStream stream;
        stream << "Unhandled exception: " << e.what();
        testResults.OnTestFailure(m_filename, m_lineNumber, m_testName, stream.GetText());
    }
    catch (...)
    {
        testResults.OnTestFailure(m_filename, m_lineNumber, m_testName, "Unhandled exception: Crash!");
    }
}


void Test::RunImpl(TestResults&) const
{
}


}
