#include "TestRunner.h"
#include "TestResults.h"
#include "Test.h"
#include "TestList.h"
#include "TestReporter.h"
#include "PrintfTestReporter.h"
#include "TimeHelpers.h"


namespace UnitTest
{


int TestRunner::RunAllTests(TestReporter& reporter, const TestList& list)
{
    Timer timer;
    timer.Start();
    
    int failureCount = 0;
    int testCount = 0;
    
    Test const* curTest = list.GetHead();
    while (curTest != 0)
    {
        ++testCount;

        TestResults result(&reporter);
        curTest->Run(result);

        if (result.Failed())
            ++failureCount;
           
        curTest = curTest->next;
    }

    float const secondsElapsed = timer.GetTimeInMs() / 1000.0f;
    
    reporter.ReportSummary(testCount, failureCount, secondsElapsed);
    
    return failureCount;
}



int DefaultRun()
{
    UnitTest::PrintfTestReporter reporter;
    return UnitTest::TestRunner().RunAllTests(reporter, Test::s_list);
}

}
