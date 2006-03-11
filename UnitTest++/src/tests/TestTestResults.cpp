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

    virtual void ReportFailure(char const*, int, char const*, char const*) 
    {
        failureReported = true;
    }

    virtual void ReportSingleResult(const std::string&, bool) {}
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

TEST_FIXTURE(MockTestResultsFixture, DefaultToSuccess)
{
    CHECK (!results.Failed());
}

TEST_FIXTURE(MockTestResultsFixture, RecordsFailures)
{
    results.ReportFailure("nothing", 0, "", "expected failure");
    CHECK(results.Failed());
}

TEST_FIXTURE(MockTestResultsFixture, PassesFailureToReporter)
{
    results.ReportFailure("nothing", 0, "", "expected failure");
    CHECK (reporter.failureReported);
}

}
