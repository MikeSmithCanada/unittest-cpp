#ifndef TYPED_TEST_CREATOR_H
#define TYPED_TEST_CREATOR_H

#include "TestLauncher.h"
#include "TestResults.h"

namespace UnitTest
{

template< typename TestClass >
class TypedTestLauncher : public TestLauncher
{
public:
    TypedTestLauncher(TestLauncher** listHead, char const* filename, int line, char const* testName)
        : TestLauncher(listHead, filename, line, testName)
    {
    }

    virtual void Launch(TestResults& testResults_) const 
    {
        try 
        {
            TestClass().Run(testResults_);
        }
        catch (...)
        {
            testResults_.ReportFailure(m_filename, m_line, m_testName, 
                        "Unhandled exception in fixture");
        }
    }
};

}

#endif

