#include "TestRunner.h"
#include "TestResults.h"
#include "Test.h"
#include "TestList.h"
#include "TestReporter.h"
#include "PrintfTestReporter.h"
#include "TimeHelpers.h"


namespace UnitTest
{

TestRunner::TestRunner()
    : m_secondsElapsed(0)
{
}


int TestRunner::RunAllTests(TestReporter& reporter, const TestList& list)
{
    ScopedTimer timer;
    
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

    reporter.ReportSummary(testCount, failureCount);
    
    m_secondsElapsed = timer.GetTimeInMs() / 1000.0f;
    return failureCount;
}


float TestRunner::GetSecondsElapsed() const
{
    return m_secondsElapsed;
}



int DefaultRun()
{
    UnitTest::PrintfTestReporter reporter;
    return UnitTest::TestRunner().RunAllTests(reporter, Test::s_list);
}

}
