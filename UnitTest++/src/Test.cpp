#include "Config.h"
#include "Test.h"
#include "TestResults.h"
#include "AssertException.h"

#ifdef TRANSLATE_POSIX_SIGNALS
    #include "SignalTranslator.h"
#endif

namespace UnitTest
{

Test::Test(std::string const testName, std::string const filename, int const lineNumber)
    : m_testName(testName)
    , m_filename(filename)
    , m_lineNumber(lineNumber)
{
}

Test::~Test()
{
}

void Test::Run(TestResults& testResults)
{
    try
    {
#ifdef TRANSLATE_POSIX_SIGNALS
        //add any signals you want translated into system exceptions here
        SignalTranslator<SIGSEGV> sigSEGV;
        SignalTranslator<SIGFPE> sigFPE;
        SignalTranslator<SIGBUS> sigBUS;
#endif
        RunImpl(testResults);
    }
    catch (AssertException const& e)
    {
        testResults.ReportFailure(e.Filename().c_str(), e.LineNumber(), e.what());
    }
    catch (std::exception const& e)
    {
        std::string const msg = std::string("Unhandled exception: ") + e.what();
        testResults.ReportFailure(m_filename.c_str(), m_lineNumber, msg);
    }
    catch (...)
    {
        testResults.ReportFailure(m_filename.c_str(), m_lineNumber, "Unhandled exception: crash!");
    }


    testResults.ReportDone(m_testName);
}
}

