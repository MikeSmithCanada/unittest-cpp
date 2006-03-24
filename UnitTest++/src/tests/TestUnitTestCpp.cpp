#include "../UnitTest++.h"
#include "../TestReporter.h"
#include "../ReportAssert.h"
#include "../Config.h"


namespace {


TEST(ValidCheckSucceeds)
{
    bool const b = true;
    CHECK(b);
}

TEST(ValidCheckEqualsSucceeds)
{
    int const x = 3;
    int const y = 3;
    CHECK_EQUAL(x, y);
}

TEST(CheckNullSucceeds)
{
    void const* nullPtr = NULL;
    CHECK_NULL(nullPtr);
}

TEST(CheckNotNullsucceeds)
{
    int const i = 3;
    int const* iPtr = &i;
    CHECK_NOT_NULL(iPtr);
}

TEST(ValidCheckCloseSucceeds)
{
    CHECK_CLOSE(2.0f, 2.001f, 0.01f);
    CHECK_CLOSE(2.001f, 2.0f, 0.01f);
}

TEST(ArrayEqualSucceeds)
{
    int const a1[] = {1,2,3};
    int const a2[] = {1,2,3};
    CHECK_ARRAY_EQUAL (a1, a2, 3);
}

TEST(ArrayCloseSucceeds)
{
    float const a1[] = {1, 2, 3};
    float const a2[] = {1, 2.01f, 3};
    CHECK_ARRAY_CLOSE (a1, a2, 3, 0.1f);
}

TEST(CheckThrowMacroSucceedsOnCorrectException)
{
    struct TestException {};
    CHECK_THROW(throw TestException(), TestException);
}

TEST(CheckAssertSucceeds)
{
    CHECK_ASSERT(UnitTest::ReportAssert("desc", "file", 0));
}


TEST(CheckThrowMacroFailsOnMissingException)
{
    class NoThrowTest : public UnitTest::Test
    {
    public:
        NoThrowTest() : Test("nothrow") {}
        void DontThrow() const
        {
        }

        virtual void RunImpl(UnitTest::TestResults& testResults_) const
        {
            CHECK_THROW(DontThrow(), int);
        }
    };

    UnitTest::TestResults results;

    NoThrowTest test;
    test.Run(results);
    CHECK_EQUAL(1, results.GetFailureCount());
}

TEST(CheckThrowMacroFailsOnWrongException)
{
    class WrongThrowTest : public UnitTest::Test
    {
    public:
        WrongThrowTest() : Test("wrongthrow") {}
        virtual void RunImpl(UnitTest::TestResults& testResults_) const
        {
            CHECK_THROW(throw "oops", int);
        }
    };

    UnitTest::TestResults results;

    WrongThrowTest test;
    test.Run(results);
    CHECK_EQUAL(1, results.GetFailureCount());
}


struct SimpleFixture
{
    SimpleFixture()
    {
        ++instanceCount;
    }
    ~SimpleFixture()
    {
        --instanceCount;
    }

    static int instanceCount;
};

int SimpleFixture::instanceCount = 0;

TEST_FIXTURE(SimpleFixture, DefaultFixtureCtorIsCalled)
{
    CHECK(SimpleFixture::instanceCount > 0);
}

TEST_FIXTURE(SimpleFixture, OnlyOneFixtureAliveAtTheTime)
{
    CHECK_EQUAL(1, SimpleFixture::instanceCount);
}

}

