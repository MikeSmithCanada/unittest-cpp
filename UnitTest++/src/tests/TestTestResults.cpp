#include "../UnitTest++.h"
#include "../TestReporter.h"
#include "../TestResults.h"

using namespace UnitTest;

namespace {


struct MockTestReporter : public TestReporter
{
public:
    MockTestReporter()
        : failureReported(false)
    {
    }

    virtual void ReportTestStart(char const*) {}
    virtual void ReportFailure(char const*, int, char const*, char const*) 
    {
        failureReported = true;
    }
    virtual void ReportSummary(int, int, float) {}

    int failureReported;
};

struct MockTestResultsFixture
{
    MockTestResultsFixture()
        : results(&reporter)
    {
    }

    MockTestReporter reporter;
    TestResults results;
};


TEST_FIXTURE(MockTestResultsFixture, StartsWithNoTestsRun)
{
    CHECK_EQUAL (0, results.GetTestCount());
}

TEST_FIXTURE(MockTestResultsFixture, RecordsNumbersOfTests)
{
    results.OnTestStart("testname1");
    results.OnTestStart("testname2");
    results.OnTestStart("testname3");
    CHECK_EQUAL(3, results.GetTestCount());
}

TEST_FIXTURE(MockTestResultsFixture, StartsWithNoTestsFailing)
{
    CHECK_EQUAL (0, results.GetFailureCount());
}

TEST_FIXTURE(MockTestResultsFixture, RecordsFailures)
{
    results.OnTestFailure("nothing", 0, "", "expected failure");
    CHECK_EQUAL(1, results.GetFailureCount());
}

TEST_FIXTURE(MockTestResultsFixture, StartsWithNoFailures)
{
    CHECK_EQUAL (0, results.GetFailureCount());
}

TEST_FIXTURE(MockTestResultsFixture, RecordsNumberOfFailures)
{
    results.OnTestFailure("nothing", 0, "", "expected failure");
    results.OnTestFailure("nothing", 0, "", "expected failure");
    CHECK_EQUAL(2, results.GetFailureCount());
}


TEST_FIXTURE(MockTestResultsFixture, PassesFailureToReporter)
{
    results.OnTestFailure("nothing", 0, "", "expected failure");
    CHECK (reporter.failureReported);
}


}
