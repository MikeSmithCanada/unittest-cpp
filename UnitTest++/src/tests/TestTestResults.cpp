#include "../UnitTest++.h"
#include "../TestResults.h"
#include "RecordingReporter.h"

using namespace UnitTest;

namespace {


TEST(StartsWithNoTestsRun)
{
    TestResults results;
    CHECK_EQUAL (0, results.GetTestCount());
}

TEST(RecordsNumbersOfTests)
{
    TestResults results;
    results.OnTestStart("testname1");
    results.OnTestStart("testname2");
    results.OnTestStart("testname3");
    CHECK_EQUAL(3, results.GetTestCount());
}

TEST(StartsWithNoTestsFailing)
{
    TestResults results;
    CHECK_EQUAL (0, results.GetFailureCount());
}

TEST(RecordsNumberOfFailures)
{
    TestResults results;
    results.OnTestFailure("nothing", 0, "", "expected failure");
    results.OnTestFailure("nothing", 0, "", "expected failure");
    CHECK_EQUAL(2, results.GetFailureCount());
}

TEST(NotifiesRecorderOfTestStartWithCorrectInfo)
{
    RecordingReporter reporter;
    TestResults results(&reporter);
    results.OnTestStart("mytest");
    CHECK_EQUAL (1, reporter.testRunCount);
    CHECK_EQUAL ("mytest", reporter.lastStartedTest);
}

TEST(NotifiesRecorderOfTestFailureWithCorrectInfo)
{
    RecordingReporter reporter;
    TestResults results(&reporter);
    results.OnTestFailure("filename", 123, "testname", "failurestring");
    CHECK_EQUAL (1, reporter.testFailedCount);
    CHECK_EQUAL ("filename", reporter.lastFailedFile);
    CHECK_EQUAL (123, reporter.lastFailedLine);
    CHECK_EQUAL ("testname", reporter.lastFailedTest);
    CHECK_EQUAL ("failurestring", reporter.lastFailedMessage);
}

TEST(NotifiesRecorderOfTestEnd)
{
    RecordingReporter reporter;
    TestResults results(&reporter);
    results.OnTestFinish("mytest", 0.1234f);
    CHECK_EQUAL (1, reporter.testFinishedCount);
    CHECK_EQUAL ("mytest", reporter.lastFinishedTest);
    CHECK_CLOSE (0.1234f, reporter.lastFinishedTestTime, 0.0001f);
}


}
