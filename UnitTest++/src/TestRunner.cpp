#include "TestRunner.h"
#include "TestLauncher.h"
#include "TestResults.h"
#include "Test.h"
#include "TestReporter.h"
#include "PrintfTestReporter.h"


namespace UnitTest
{

TestRunner::TestRunner()
    : m_testLauncherListHead(TestLauncher::GetHeadAddr())
{
}

void TestRunner::SetTestLauncherListHead(TestLauncher** listHead)
{
    m_testLauncherListHead = listHead;
}

int TestRunner::RunAllTests(TestReporter& reporter)
{
    int failureCount = 0;

    int testCount = 0;
    TestLauncher const* curLauncher = *m_testLauncherListHead;
    while (curLauncher)
    {
        ++testCount;

        TestResults result(&reporter);
        curLauncher->Launch(result);

        if (result.Failed())
            ++failureCount;
           
        curLauncher = curLauncher->GetNext();
    }

    reporter.ReportSummary(testCount, failureCount);
    
    return failureCount;
}



int DefaultRun()
{
    UnitTest::PrintfTestReporter reporter;
    return UnitTest::TestRunner().RunAllTests(reporter);
}

}
