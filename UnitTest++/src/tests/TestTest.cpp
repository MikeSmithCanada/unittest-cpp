#include "../UnitTest++.h"
#include "../TestReporter.h"


namespace {


TEST (PassingTestHasNoFailures)
{
    class PassingTest : public UnitTest::Test
    {
    public:
        virtual void RunImpl(UnitTest::TestResults& testResults_)
        {
            CHECK(true);
        }
    };

    UnitTest::TestResults results;
    PassingTest().Run(results);
    CHECK(!results.Failed());
}


TEST (FailingTestHasFailures)
{
    class FailingTest : public UnitTest::Test
    {
    public:
        virtual void RunImpl(UnitTest::TestResults& testResults_)
        {
            CHECK(false);
        }
    };

    UnitTest::TestResults results;
    FailingTest().Run(results);
    CHECK(results.Failed());
}


TEST (CrashingTestsAreReportedAsFailures)
{
    class CrashingTest : public UnitTest::Test
    {
    public:
        virtual void RunImpl(UnitTest::TestResults&)
        {
            throw "Blah";
        }
    };

    UnitTest::TestResults results;
    CrashingTest().Run(results);
}


}
