#include "../UnitTest++.h"
#include "../TestReporter.h"


namespace {


struct DoNothingReporter : public UnitTest::TestReporter
{
public:
    virtual void ReportFailure(char const*, int, const char*, std::string) {}
    virtual void ReportSingleResult(const std::string&, bool) {}
    virtual void ReportSummary(int, int) {}
};

struct ResultsFixture
{
    ResultsFixture() : results(reporter) {}
    DoNothingReporter reporter;
    UnitTest::TestResults results;
};


TEST_FIXTURE (ResultsFixture, PassingTestHasNoFailures)
{
    class PassingTest : public UnitTest::Test
    {
    public:
        virtual void RunImpl(UnitTest::TestResults& testResults_)
        {
            CHECK(true);
        }
    };

    PassingTest().Run(results);
    CHECK(!results.Failed());
}


TEST_FIXTURE (ResultsFixture, FailingTestHasFailures)
{
    class FailingTest : public UnitTest::Test
    {
    public:
        virtual void RunImpl(UnitTest::TestResults& testResults_)
        {
            CHECK(false);
        }
    };

    FailingTest().Run(results);
    CHECK(results.Failed());
}


TEST_FIXTURE (ResultsFixture, CrashingTestsAreReportedAsFailures)
{
    class CrashingTest : public UnitTest::Test
    {
    public:
        virtual void RunImpl(UnitTest::TestResults&)
        {
            throw "Blah";
        }
    };

    CrashingTest().Run(results);
}

}
