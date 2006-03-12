#include "../UnitTest++.h"
#include "RecordingReporter.h"
#include "../ReportAssert.h"
#include "../TestList.h"
#include "../TimeHelpers.h"

using namespace UnitTest;

namespace
{

struct MockTest : public Test
{
    MockTest(char const* testName, bool const success_, bool const assert_)
        : Test(testName)
        , success(success_)
        , asserted(assert_)
    {
    }

    virtual void RunImpl(TestResults& testResults_) const
    {
        if (asserted)
            ReportAssert("desc", "file", 0);
        else if (!success)
            testResults_.OnTestFailure("filename", 0, "", "message");
    }

    bool success;
    bool asserted;
};


struct TestRunnerFixture
{
    RecordingReporter reporter;
    TestList list;
};

TEST_FIXTURE(TestRunnerFixture, FailureCountIsZeroWhenNoTestsAreRun)
{
    CHECK_EQUAL(0, RunAllTests(reporter, list));
    CHECK_EQUAL(0, reporter.testRunCount);
    CHECK_EQUAL(0, reporter.testFailedCount);
}

TEST_FIXTURE(TestRunnerFixture, PassingTestsAreReportedCorrectly)
{
    MockTest test("goodtest", true, false);
    list.Add(&test); 

    RunAllTests(reporter, list);
    CHECK_EQUAL(1, reporter.testRunCount);
    CHECK_EQUAL(0, reporter.testFailedCount);
    CHECK_EQUAL(std::string("goodtest"), reporter.lastReportedTest);
}

TEST_FIXTURE(TestRunnerFixture, TestRunnerCallsReportFailureOncePerFailingTest)
{
    MockTest test1("test", false, false);
    list.Add(&test1);
    MockTest test2("test", false, false);
    list.Add(&test2);

    CHECK_EQUAL(2, RunAllTests(reporter, list));
    CHECK_EQUAL(2, reporter.testFailedCount);
}

TEST_FIXTURE(TestRunnerFixture, TestsThatAssertAreReportedAsFailing)
{
    MockTest test("test", true, true);
    list.Add(&test);

    RunAllTests(reporter, list);
    CHECK_EQUAL(1, reporter.testFailedCount);
}


TEST_FIXTURE(TestRunnerFixture, FinishedTestsReportDone)
{
    MockTest test1("test", true, false);
    MockTest test2("test", false, false);
    list.Add(&test1);
    list.Add(&test2);

    RunAllTests(reporter, list);
    CHECK_EQUAL(2, reporter.summaryTestCount);
    CHECK_EQUAL(1, reporter.summaryFailureCount);
}

struct SlowTest : public Test
{
    SlowTest() : Test("slow")
    {
    }

    virtual void RunImpl(TestResults&) const
    {
        TimeHelpers::SleepMs(100);
    }
};

TEST_FIXTURE(TestRunnerFixture, ReportedTimeElapsedForRunIsNonZero)
{
    SlowTest test;
    list.Add(&test); 

    RunAllTests(reporter, list);    
    CHECK (reporter.summarySecondsElapsed > 0);
}


}

