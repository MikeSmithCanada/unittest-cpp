#include "../UnitTest++.h"
#include "../TestReporter.h"
#include "../ReportAssert.h"
#include "../TestList.h"
#include "../TimeHelpers.h"

using namespace UnitTest;

namespace
{

struct MockTestReporter : public TestReporter
{
public:
    MockTestReporter()
        : failureCount(0)
        , lastLine(0)
        , execCount(0)        
        , testCount(0)
        , secondsElapsed(0)
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

    virtual void ReportSummary(int testCount_, int, float secondsElapsed_) 
    {
        testCount = testCount_;
        secondsElapsed = secondsElapsed_;
    }

    virtual void ReportSingleResult(char const*, bool)
    {
        ++execCount;
    }

    int failureCount;
    std::string lastFile;
    int lastLine;
    std::string lastTest;
    std::string lastFailure;
    
    int execCount;
    
    int testCount;
    float secondsElapsed;
};

struct MockTest : public Test
{
    MockTest(bool const success_, bool const assert_)
        : Test("mock")
        , success(success_)
        , asserted(assert_)
    {
    }

    virtual void RunImpl(TestResults& testResults_) const
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
    TestList list;
};

TEST_FIXTURE(TestRunnerFixture, FailureCountIsZeroWhenNoTestsAreRun)
{
    CHECK_EQUAL(0, RunAllTests(reporter, list));
    CHECK_EQUAL(0, reporter.testCount);
    CHECK_EQUAL(0, reporter.execCount);
}

TEST_FIXTURE(TestRunnerFixture, PassingTestsAreNotReportedAsFailures)
{
    MockTest test(true, false);
    list.Add(&test); 

    CHECK_EQUAL(0, RunAllTests(reporter, list));
    CHECK_EQUAL(0, reporter.failureCount);
    CHECK_EQUAL(1, reporter.testCount);
}

TEST_FIXTURE(TestRunnerFixture, FinishedTestsReportDone)
{
    MockTest test1(true, false);
    MockTest test2(false, false);
    list.Add(&test1);
    list.Add(&test2);

    RunAllTests(reporter, list);
    CHECK_EQUAL(2, reporter.execCount);
}


TEST_FIXTURE(TestRunnerFixture, TestRunnerCallsReportFailureOncePerFailingTest)
{
    MockTest test1(false, false);
    MockTest test2(false, false);
    list.Add(&test1);
    list.Add(&test2);

    CHECK_EQUAL(2, RunAllTests(reporter, list));
    CHECK_EQUAL(2, reporter.failureCount);
}

TEST_FIXTURE(TestRunnerFixture, TestsThatAssertAreReportedAsFailing)
{
    MockTest test(true, true);
    list.Add(&test);

    RunAllTests(reporter, list);
    CHECK_EQUAL(1, reporter.failureCount);
}

// TODO: Is there any way to test that a test with a fixture throwing an exception is reported 
// as a failure with the correct information?


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
    CHECK (reporter.secondsElapsed > 0);
}


}

