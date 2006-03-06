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
        , lastLine(0)
    {
    }

    
    virtual void ReportFailure(char const* file, int line, const char* testName, std::string failure)
    {
        ++failureCount;
        lastFile = file;
        lastLine = line;
        lastTest = testName;
        lastFailure = failure;
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
    std::string lastFile;
    int lastLine;
    std::string lastTest;
    std::string lastFailure;
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
        : TestLauncher(listHead, "", 0, "")
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


struct CrashingFixtureTest : public Test
{
    CrashingFixtureTest()
    {
        throw "Exception in fixture!";
    }

    virtual void RunImpl(TestResults& testResults_) {}
};


TEST_FIXTURE(TestRunnerFixture, TestsThatCrashInFixtureAreReportedAsFailing)
{
    TypedTestLauncher<CrashingFixtureTest> launcher(&listHead, "", 0, "");
    runner.RunAllTests(reporter);
    CHECK_EQUAL(1, reporter.failureCount);
}

TEST_FIXTURE(TestRunnerFixture, TestsThatCrashInFixtureHaveCorrectFailureInfo)
{
    TypedTestLauncher<CrashingFixtureTest> launcher(&listHead, "Hello", 123, "TestNameYadda");
    runner.RunAllTests(reporter);

    CHECK_EQUAL (std::string("Hello"), reporter.lastFile);
    CHECK_EQUAL (123, reporter.lastLine);
    CHECK_EQUAL (std::string("TestNameYadda"), reporter.lastTest);
    CHECK (reporter.lastFailure.find("fixture") != std::string::npos );
    CHECK (reporter.lastFailure.find("exception") != std::string::npos );

}

}

