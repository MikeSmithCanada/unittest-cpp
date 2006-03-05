#include "TestRunner.h"
#include "TestLauncher.h"
#include "TestResults.h"
#include "Test.h"
#include "TestReporter.h"


namespace UnitTest
{

TestRunner::TestRunner(TestReporter& reporter)
    : m_testReporter(reporter)
    , m_testLauncherListHead(TestLauncher::GetHeadAddr())
{
}

void TestRunner::SetTestLauncherListHead(TestLauncher** listHead)
{
    m_testLauncherListHead = listHead;
}

int TestRunner::RunAllTests()
{
    int failureCount = 0;

    int testCount = 0;
    TestLauncher const* curLauncher = *m_testLauncherListHead;
    while (curLauncher)
    {
        ++testCount;

        TestResults result(m_testReporter);
        curLauncher->Launch(result);

        if (result.Failed())
            ++failureCount;

        curLauncher = curLauncher->GetNext();
    }

    m_testReporter.ReportSummary(testCount, failureCount);

    return failureCount;
}

}

