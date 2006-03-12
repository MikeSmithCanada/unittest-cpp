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
{
}

Test::~Test()
{
}

void Test::Run(TestResults& testResults) const
{
    //printf ("%s\n", m_testName.c_str());

    testResults.OnTestStart(m_testName);
    
    try
    {
#ifdef LINUX
        SignalTranslator sig;
#endif
        RunImpl(testResults);
    }
    catch (AssertException const& e)
    {
        testResults.OnTestFailure(e.Filename(), e.LineNumber(), m_testName, e.what());
    }
    catch (std::exception const& e)
    {
        char msg[512];
        std::strcpy (msg, "Unhandled exception: ");
        std::strcat (msg, e.what());
        testResults.OnTestFailure(m_filename, m_lineNumber, m_testName, msg);
    }
    catch (...)
    {
        testResults.OnTestFailure(m_filename, m_lineNumber, m_testName, "Unhandled exception: crash!");
    }
}


void Test::RunImpl(TestResults&) const
{
}


}

