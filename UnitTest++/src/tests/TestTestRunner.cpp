#include "../UnitTest++.h"
#include "../TestReporter.h"
#include "../ReportAssert.h"

using namespace UnitTest;

namespace
{

struct MockTestReporter : public TestReporter
{
public:
    MockTestReporter()
        : failureCount(0)
        , testCount(0)
        , execCount(0)
    {
    }

    virtual void ReportFailure(char const*, int, const char*, std::string)
    {
        ++failureCount;
    }

    virtual void ReportSummary(int testCount_, int) 
    {
        testCount = testCount_;
    }

    virtual void ReportSingleResult(const std::string&, bool)
    {
        ++execCount;
    }

    int failureCount;
    int testCount;
    int execCount;
};

struct MockTest : public Test
{
    MockTest(bool const success_, bool const assert_)
        : success(success_)
        , asserted(assert_)
    {
    }

    virtual void RunImpl(TestResults& testResults_)
    {
        if (asserted)
            ReportAssert("desc", "file", 0);
        else if (!success)
            testResults_.ReportFailure("filename", 0, "", "message");
    }

    bool success;
    bool asserted;
};


struct TestRunnerFixture
{
    TestRunnerFixture()
        : listHead(0)
    {
        runner.SetTestLauncherListHead(&listHead);
    }

    MockTestReporter reporter;
    TestRunner runner;
    TestLauncher* listHead;
};

TEST_FIXTURE(TestRunnerFixture, FailureCountIsZeroWhenNoTestsAreRun)
{
    CHECK_EQUAL(0, runner.RunAllTests(reporter));
    CHECK_EQUAL(0, reporter.testCount);
    CHECK_EQUAL(0, reporter.execCount);
}


struct MockTestLauncher : public TestLauncher
{
public:
    MockTestLauncher(TestLauncher** listHead)
        : TestLauncher(listHead)
        , success(true)
        , asserted(false)
    {
    }

    void Launch(TestResults& results) const 
    { 
        MockTest(success, asserted).Run(results); 
    }

    bool success;
    bool asserted;
};


TEST_FIXTURE(TestRunnerFixture, PassingTestsAreNotReportedAsFailures)
{
    MockTestLauncher launcher(&listHead);
    launcher.success = true;

    CHECK_EQUAL(0, runner.RunAllTests(reporter));
    CHECK_EQUAL(0, reporter.failureCount);
    CHECK_EQUAL(1, reporter.testCount);
}

TEST_FIXTURE(TestRunnerFixture, FinishedTestsReportDone)
{
    MockTestLauncher launcher1(&listHead);
    MockTestLauncher launcher2(&listHead);
    launcher1.success = false;
    launcher2.success = true;

    runner.RunAllTests(reporter);
    CHECK_EQUAL(2, reporter.execCount);
}

TEST_FIXTURE(TestRunnerFixture, TestRunnerCallsReportFailureOncePerFailingTest)
{
    MockTestLauncher launcher1(&listHead);
    MockTestLauncher launcher2(&listHead);
    launcher1.success = false;
    launcher2.success = false;

    CHECK_EQUAL(2, runner.RunAllTests(reporter));
    CHECK_EQUAL(2, reporter.failureCount);
}

TEST_FIXTURE(TestRunnerFixture, TestsThatAssertAreReportedAsFailing)
{
    MockTestLauncher launcher(&listHead);
    launcher.asserted = true;

    runner.RunAllTests(reporter);
    CHECK_EQUAL(1, reporter.failureCount);
}

}

