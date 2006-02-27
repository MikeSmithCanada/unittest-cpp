#include "../UnitTest++.h"
#include "../TestReporter.h"


namespace {


struct DoNothingReporter : public UnitTest::TestReporter
{
public:
    virtual void ReportFailure(char const*, int, std::string) {}
    virtual void ReportSingleResult(const std::string&, bool) {}
    virtual void ReportSummary(int, int) {}
};


struct ResultsFixture
{
    ResultsFixture() : results(reporter) {}
    DoNothingReporter reporter;
    UnitTest::TestResults results;
};



class PassingTest : public UnitTest::Test
{
public:
    virtual void RunImpl(UnitTest::TestResults& testResults_)
    {
        CHECK(true);
    }
};

TEST_FIXTURE (ResultsFixture, PassingTestHasNoFailures)
{
    PassingTest().Run(results);
    CHECK(!results.Failed());
}


class FailingTest : public UnitTest::Test
{
public:
    virtual void RunImpl(UnitTest::TestResults& testResults_)
    {
        CHECK(false);
    }
};

TEST_FIXTURE (ResultsFixture, FailingTestHasNoFailures)
{
    FailingTest().Run(results);
    CHECK(results.Failed());
}


class CrashingTest : public UnitTest::Test
{
public:
    virtual void RunImpl(UnitTest::TestResults&)
    {
        reinterpret_cast< void (*)() >(0)();
    }
};

TEST_FIXTURE (ResultsFixture, CrashingTestsAreReportedAsFailures)
{
    CrashingTest().Run(results);
    CHECK(results.Failed());
}

}
