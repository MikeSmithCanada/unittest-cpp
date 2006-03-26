#include "TestRunner.h"
#include "TestResults.h"
#include "Test.h"
#include "TestList.h"
#include "TestReporter.h"
#include "TestReporterStdout.h"
#include "TimeHelpers.h"
#include <cstdio>

namespace UnitTest
{


int RunAllTests(TestReporter& reporter, TestList const& list, int const maxTestTimeInMs )
{
    TestResults result(&reporter);

    Timer overallTimer;
    overallTimer.Start();

    Test const* curTest = list.GetHead();
    while (curTest != 0)
    {
        Timer testTimer;
        testTimer.Start();
        result.OnTestStart(curTest->m_testName);

        curTest->Run(result);

        int const testTimeInMs = testTimer.GetTimeInMs();
        if (maxTestTimeInMs > 0 && testTimeInMs > maxTestTimeInMs)
        {
            char txt[256];
            std::sprintf (txt, "Global time constraint failed. Expected under %i ms but took %i ms.",
                            maxTestTimeInMs, testTimeInMs);
            result.OnTestFailure(curTest->m_filename, curTest->m_lineNumber, 
                                 curTest->m_testName, txt);
        }
        result.OnTestFinish(curTest->m_testName, testTimeInMs/1000.0f);

        curTest = curTest->next;
    }

    float const secondsElapsed = overallTimer.GetTimeInMs() / 1000.0f;
    reporter.ReportSummary(result.GetTestCount(), result.GetFailureCount(), secondsElapsed);

    return result.GetFailureCount();
}


int RunAllTests()
{
    TestReporterStdout reporter;
    return RunAllTests(reporter, Test::GetTestList());
}

}
