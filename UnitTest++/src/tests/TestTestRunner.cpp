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

    
    virtual void ReportFailure(char const* file, int line, char const* testName, char const* failure)
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
        : Test("", "", 0)
        , success(success_)
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
    MockTestReporter reporter;
    TestRunner runner;
};

TEST_FIXTURE(TestRunnerFixture, FailureCountIsZeroWhenNoTestsAreRun)
{
    CHECK_EQUAL(0, runner.RunAllTests(reporter, 0));
    CHECK_EQUAL(0, reporter.testCount);
    CHECK_EQUAL(0, reporter.execCount);
}

TEST_FIXTURE(TestRunnerFixture, PassingTestsAreNotReportedAsFailures)
{
    MockTest test(true, false);        

    CHECK_EQUAL(0, runner.RunAllTests(reporter, &test));
    CHECK_EQUAL(0, reporter.failureCount);
    CHECK_EQUAL(1, reporter.testCount);
}

TEST_FIXTURE(TestRunnerFixture, FinishedTestsReportDone)
{
    MockTest test1(true, false);
    MockTest test2(false, false);
    test1.next = &test2;

    runner.RunAllTests(reporter, &test1);
    CHECK_EQUAL(2, reporter.execCount);
}


TEST_FIXTURE(TestRunnerFixture, TestRunnerCallsReportFailureOncePerFailingTest)
{
    MockTest test1(false, false);
    MockTest test2(false, false);
    test1.next = &test2;

    CHECK_EQUAL(2, runner.RunAllTests(reporter, &test1));
    CHECK_EQUAL(2, reporter.failureCount);
}

TEST_FIXTURE(TestRunnerFixture, TestsThatAssertAreReportedAsFailing)
{
    MockTest test(true, true);

    runner.RunAllTests(reporter, &test);
    CHECK_EQUAL(1, reporter.failureCount);
}

// TODO: Is there any way to test that a test with a fixture throwing an exception is reported 
// as a failure with the correct information?

}

