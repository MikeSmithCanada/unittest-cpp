#include "TestRunner.h"
#include "TestResults.h"
#include "Test.h"
#include "TestList.h"
#include "TestReporter.h"
#include "TestReporterStdout.h"
#include "TimeHelpers.h"


namespace UnitTest
{


int RunAllTests(TestReporter& reporter, const TestList& list)
{
    TestResults result(&reporter);

    Timer timer;
    timer.Start();

    Test const* curTest = list.GetHead();
    while (curTest != 0)
    {
        curTest->Run(result);
        curTest = curTest->next;
    }

    float const secondsElapsed = timer.GetTimeInMs() / 1000.0f;
    reporter.ReportSummary(result.GetTestCount(), result.GetFailureCount(), secondsElapsed);

    return result.GetFailureCount();
}


int RunAllTests()
{
    TestReporterStdout reporter;
    return RunAllTests(reporter, Test::GetTestList());
}

}
