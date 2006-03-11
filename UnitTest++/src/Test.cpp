#include "Config.h"
#include "Test.h"
#include "TestResults.h"
#include "AssertException.h"

#ifdef LINUX
    #include "Linux/SignalTranslator.h"
#endif

#include <cstring>


namespace UnitTest
{

TestList Test::s_list;



Test::Test(char const* testName, char const* filename, int const lineNumber)
    : next(0)
    , m_testName(testName)
    , m_filename(filename)
    , m_lineNumber(lineNumber)
{
}

Test::~Test()
{
}

void Test::Run(TestResults& testResults) const
{
    //printf ("%s\n", m_testName.c_str());

    try
    {
#ifdef LINUX
        SignalTranslator sig;
#endif
        RunImpl(testResults);
    }
    catch (AssertException const& e)
    {
        testResults.ReportFailure(e.Filename(), e.LineNumber(), m_testName, e.what());
    }
    catch (std::exception const& e)
    {
        char msg[512];
        std::strcpy (msg, "Unhandled exception: ");
        std::strcat (msg, e.what());
        testResults.ReportFailure(m_filename, m_lineNumber, m_testName, msg);
    }
    catch (...)
    {
        testResults.ReportFailure(m_filename, m_lineNumber, m_testName, "Unhandled exception: crash!");
    }

    testResults.ReportDone(m_testName);
}


void Test::RunImpl(TestResults&) const
{
}


}

