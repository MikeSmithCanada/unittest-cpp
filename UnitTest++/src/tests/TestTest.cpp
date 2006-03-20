#include "../UnitTest++.h"
#include "../TestReporter.h"


namespace {


TEST (PassingTestHasNoFailures)
{
    class PassingTest : public UnitTest::Test
    {
    public:
        PassingTest() : Test("passing") {}
        virtual void RunImpl(UnitTest::TestResults& testResults_) const
        {
            CHECK(true);
        }
    };

    UnitTest::TestResults results;
    PassingTest().Run(results);
    CHECK_EQUAL(0, results.GetFailureCount());
}


TEST (FailingTestHasFailures)
{
    class FailingTest : public UnitTest::Test
    {
    public:
        FailingTest() : Test("failing") {}
        virtual void RunImpl(UnitTest::TestResults& testResults_) const
        {
            CHECK(false);
        }
    };

    UnitTest::TestResults results;
    FailingTest().Run(results);
    CHECK_EQUAL(1, results.GetFailureCount());
}


TEST (ThrowingTestsAreReportedAsFailures)
{
    class CrashingTest : public UnitTest::Test
    {
    public:
        CrashingTest() : Test("throwing") {}
        virtual void RunImpl(UnitTest::TestResults&) const
        {
            throw "Blah";
        }
    };

    UnitTest::TestResults results;
    CrashingTest().Run(results);
    CHECK_EQUAL(1, results.GetFailureCount());
}

#if !defined(LINUX) && !defined(__APPLE__)

TEST (CrashingTestsAreReportedAsFailures)
{
    class CrashingTest : public UnitTest::Test
    {
    public:
        CrashingTest() : Test("crashing") {}
        virtual void RunImpl(UnitTest::TestResults&) const
        {
            reinterpret_cast< void (*)() >(0)();
        }
    };

    UnitTest::TestResults results;
    CrashingTest().Run(results);
    CHECK_EQUAL(1, results.GetFailureCount());
}

#endif

}
