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
    TypedTestLauncher(TestLauncher** listHead)
        : TestLauncher(listHead)
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
            testResults_.ReportFailure("", 0, "", 
                        "Unhandled exception in fixture");
        }
    }
};

}

#endif

