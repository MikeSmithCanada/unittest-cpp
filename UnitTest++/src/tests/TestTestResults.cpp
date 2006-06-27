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
	TestDetails details1("testname1");
	TestDetails details2("testname2");
	TestDetails details3("testname3");

    results.OnTestStart(details1);
    results.OnTestStart(details2);
    results.OnTestStart(details3);
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
    TestDetails details("test", "suite", "file", 1);

    // Test both overloads
    results.OnTestFailure(details, "nothing", 0, "expected failure");
    results.OnTestFailure(details, "expected failure");
    CHECK_EQUAL(2, results.GetFailureCount());
}

TEST(NotifiesReporterOfTestStartWithCorrectInfo)
{
    RecordingReporter reporter;
    TestResults results(&reporter);
    TestDetails details("testname", "suitename", "filename", 123);
    results.OnTestStart(details);
    CHECK_EQUAL (1, reporter.testRunCount);
    CHECK_EQUAL ("suitename", reporter.lastStartedSuite);
    CHECK_EQUAL ("testname", reporter.lastStartedTest);
}

TEST(NotifiesReporterOfTestFailureWithCorrectInfo)
{
    RecordingReporter reporter;
    TestResults results(&reporter);
    TestDetails details("testname", "suitename", "filename", 123);
    
    results.OnTestFailure(details, "failurestring");
    CHECK_EQUAL (1, reporter.testFailedCount);
    CHECK_EQUAL ("filename", reporter.lastFailedFile);
    CHECK_EQUAL (123, reporter.lastFailedLine);
    CHECK_EQUAL ("suitename", reporter.lastFailedSuite);
    CHECK_EQUAL ("testname", reporter.lastFailedTest);
    CHECK_EQUAL ("failurestring", reporter.lastFailedMessage);
}

TEST(NotifiesReporterOfCheckFailureWithCorrectInfo)
{
    RecordingReporter reporter;
    TestResults results(&reporter);
    TestDetails details("testname", "suitename", "filename", 123);

    // The file/line parameters should take precedence over the test details
    results.OnTestFailure(details, "checkfilename", 321, "failurestring");
    CHECK_EQUAL (1, reporter.testFailedCount);
    CHECK_EQUAL ("checkfilename", reporter.lastFailedFile);
    CHECK_EQUAL (321, reporter.lastFailedLine);

    CHECK_EQUAL ("testname", reporter.lastFailedTest);
    CHECK_EQUAL ("suitename", reporter.lastFailedSuite);
    CHECK_EQUAL ("failurestring", reporter.lastFailedMessage);
}

TEST(NotifiesReporterOfTestEnd)
{
    RecordingReporter reporter;
    TestResults results(&reporter);
    TestDetails details("testname", "suitename", "filename", 123);

    results.OnTestFinish(details, 0.1234f);
    CHECK_EQUAL (1, reporter.testFinishedCount);
    CHECK_EQUAL ("testname", reporter.lastFinishedTest);
    CHECK_EQUAL ("suitename", reporter.lastFinishedSuite);
    CHECK_CLOSE (0.1234f, reporter.lastFinishedTestTime, 0.0001f);
}


}
