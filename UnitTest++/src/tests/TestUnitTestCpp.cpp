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

TEST(CheckEqualMacroAllowsCharPtrAndStringComparisons)
{
    const std::string str("Hello World");
    CHECK_EQUAL(std::string("Hello World"), str);
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
        void DontThrow()
        {
        }

#ifdef VISUAL_STUDIO_2003
#   pragma warning(push)
#   pragma warning(disable: 4702) // "unreachable code"
#endif
        virtual void RunImpl(UnitTest::TestResults& testResults_)
        {
            CHECK_THROW(DontThrow(), int);
        }
#ifdef VISUAL_STUDIO_2003
#   pragma warning(pop)
#endif
    };

    UnitTest::TestResults results;

    NoThrowTest test;
    test.Run(results);
    CHECK(results.Failed());
}

TEST(CheckThrowMacroFailsOnWrongException)
{
    class WrongThrowTest : public UnitTest::Test
    {
    public:
        virtual void RunImpl(UnitTest::TestResults& testResults_)
        {
            CHECK_THROW(throw "oops", int);
        }
    };

    UnitTest::TestResults results;

    WrongThrowTest test;
    test.Run(results);
    CHECK(results.Failed());
}


struct SimpleFixture
{
    SimpleFixture()
    {
        constructed = true;
    }

    static bool constructed;
};

bool SimpleFixture::constructed = false;

TEST_FIXTURE(SimpleFixture, DefaultFixtureCtorIsCalled)
{
    CHECK(SimpleFixture::constructed);
}


struct SpecializedCtorFixture
{
    SpecializedCtorFixture(int value_ = 0) : value(value_)  {}
    int const value;
};

TEST_FIXTURE_CTOR(SpecializedCtorFixture, (5), CtorDataGetsPassedToFixture)
{
    CHECK_EQUAL(5, value);
}

}

