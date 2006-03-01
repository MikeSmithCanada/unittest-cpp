#include "../UnitTest++.h"


namespace {

struct DoNothingReporter : public UnitTest::TestReporter
{
public:
    virtual void ReportFailure(char const*, int, std::string) {}
    virtual void ReportSingleResult(const std::string&, bool) {}
    virtual void ReportSummary(int, int) {}
};


TEST(CheckSuceedsOnTrue)
{
    bool failure = true;
    {
        DoNothingReporter reporter;
        UnitTest::TestResults testResults_(reporter);
        CHECK (true);
        failure = testResults_.Failed();
    }

    CHECK (!failure);
}

TEST(CheckFailsOnFalse)
{
    bool failure = false;
    {
        DoNothingReporter reporter;
        UnitTest::TestResults testResults_(reporter);
        CHECK (false);
        failure = testResults_.Failed();
    }

    CHECK (failure);
}

int ThrowingFunction()
{
    throw "Doh";
    return 1;
}

TEST(CheckFailsOnException)
{
    bool failure = false;
    {
        DoNothingReporter reporter;
        UnitTest::TestResults testResults_(reporter);
        CHECK (ThrowingFunction() == 1);
        failure = testResults_.Failed();
    }

    CHECK (failure);
}

TEST(CheckEqualSuceedsOnEqual)
{
    bool failure = true;
    {
        DoNothingReporter reporter;
        UnitTest::TestResults testResults_(reporter);
        CHECK_EQUAL (1, 1);
        failure = testResults_.Failed();
    }

    CHECK (!failure);
}

TEST(CheckEqualFailsOnNotEqual)
{
    bool failure = false;
    {
        DoNothingReporter reporter;
        UnitTest::TestResults testResults_(reporter);
        CHECK_EQUAL (1, 2);
        failure = testResults_.Failed();
    }

    CHECK (failure);
}

TEST(CheckEqualFailsOnException)
{
    bool failure = false;
    {
        DoNothingReporter reporter;
        UnitTest::TestResults testResults_(reporter);
        CHECK_EQUAL (ThrowingFunction(), 1);
        failure = testResults_.Failed();
    }

    CHECK (failure);
}

TEST(CheckCloseSuceedsOnEqual)
{
    bool failure = true;
    {
        DoNothingReporter reporter;
        UnitTest::TestResults testResults_(reporter);
        CHECK_CLOSE (1.0f, 1.001f, 0.01f);
        failure = testResults_.Failed();
    }

    CHECK (!failure);
}

TEST(CheckCloseFailsOnNotEqual)
{
    bool failure = false;
    {
        DoNothingReporter reporter;
        UnitTest::TestResults testResults_(reporter);
        CHECK_CLOSE (1.0f, 1.1f, 0.01f);
        failure = testResults_.Failed();
    }

    CHECK (failure);
}

TEST(CheckCloseFailsOnException)
{
    bool failure = false;
    {
        DoNothingReporter reporter;
        UnitTest::TestResults testResults_(reporter);
        CHECK_CLOSE ((float)ThrowingFunction(), 1.0001f, 0.1f);
        failure = testResults_.Failed();
    }

    CHECK (failure);
}

TEST(CheckArrayEqualSuceedsOnEqual)
{
    bool failure = true;
    {
        DoNothingReporter reporter;
        UnitTest::TestResults testResults_(reporter);
        const float data[4] = { 0, 1, 2, 3 };
        CHECK_ARRAY_EQUAL (data, data, 3);
        failure = testResults_.Failed();
    }

    CHECK (!failure);
}

TEST(CheckArrayEqualFailsOnNotEqual)
{
    bool failure = false;
    {
        DoNothingReporter reporter;
        UnitTest::TestResults testResults_(reporter);
        const float data1[4] = { 0, 1, 2, 3 };
        const float data2[4] = { 0, 1, 3, 3 };
        CHECK_ARRAY_EQUAL (data1, data2, 3);
        failure = testResults_.Failed();
    }

    CHECK (failure);
}

TEST(CheckArrayCloseSuceedsOnEqual)
{
    bool failure = true;
    {
        DoNothingReporter reporter;
        UnitTest::TestResults testResults_(reporter);
        const float data[4] = { 0, 1, 2, 3 };
        CHECK_ARRAY_CLOSE (data, data, 3, 0.01f);
        failure = testResults_.Failed();
    }

    CHECK (!failure);
}

TEST(CheckArrayCloseFailsOnNotEqual)
{
    bool failure = false;
    {
        DoNothingReporter reporter;
        UnitTest::TestResults testResults_(reporter);
        const float data1[4] = { 0, 1, 2, 3 };
        const float data2[4] = { 0, 1, 3, 3 };
        CHECK_ARRAY_CLOSE (data1, data2, 3, 0.01f);
        failure = testResults_.Failed();
    }

    CHECK (failure);
}


/*
class ThrowingObject
{
public:
    float operator[](int index) const
    {
        const float data[4] = { 0, 1, 2, 3 };
        throw "Test throw";
        return data[index];
    }
};

TEST(CheckArrayCloseFailsOnException)
{
    bool failure = false;
    {
        DoNothingReporter reporter;
        UnitTest::TestResults testResults_(reporter);
        const float data[4] = { 0, 1, 2, 3 };
        ThrowingObject obj;
        CHECK_ARRAY_CLOSE (data, obj, 3, 0.01f);
        failure = testResults_.Failed();
    }

    CHECK (failure);
}
*/

}
