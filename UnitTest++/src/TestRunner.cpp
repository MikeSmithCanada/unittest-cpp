#include "TestRunner.h"
#include "TestResults.h"
#include "Test.h"
#include "TestList.h"
#include "TestReporter.h"
#include "PrintfTestReporter.h"


namespace UnitTest
{


int TestRunner::RunAllTests(TestReporter& reporter, TestList& list)
{
    int failureCount = 0;

    int testCount = 0;
    Test* curTest = list.GetHead();
    while (curTest != 0)
    {
        ++testCount;

        TestResults result(&reporter);
        curTest->Run(result);

        if (result.Failed())
            ++failureCount;
           
        curTest = curTest->next;
    }

    reporter.ReportSummary(testCount, failureCount);
    
    return failureCount;
}



int DefaultRun()
{
    UnitTest::PrintfTestReporter reporter;
    return UnitTest::TestRunner().RunAllTests(reporter, Test::s_list);
}

}
