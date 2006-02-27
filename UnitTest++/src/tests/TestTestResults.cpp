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

    virtual void ReportFailure(char const*, int, std::string) 
    {
        failureReported = true;
    }
    
    virtual void ReportSingleResult(const std::string&, bool) {}
    virtual void ReportSummary(int, int) {}

    int failureReported;
};

struct MockTestResultsFixture
{
    MockTestResultsFixture()
        : results(reporter)
    {
    }

    MockTestReporter reporter;
    TestResults results;
};

TEST_FIXTURE(MockTestResultsFixture, TestResultsDefaultToSuccess)
{
    CHECK (!results.Failed());
}

TEST_FIXTURE(MockTestResultsFixture, TestResultsRecordFailures)
{
    results.ReportFailure("nothing", 0, "expected failure");
    CHECK(results.Failed());
}

TEST_FIXTURE(MockTestResultsFixture, TestResultsReportFailures)
{
    results.ReportFailure("nothing", 0, "expected failure");
    CHECK (reporter.failureReported);
}

}
