#include "../UnitTest++.h"

using namespace UnitTest;


namespace {

TEST(CheckCloseTrue)
{
    CHECK(CheckClose(3.001f, 3.0f, 0.1f));
}

TEST(CheckCloseFalse)
{
    CHECK(false == CheckClose(3.12f, 3.0f, 0.1f));
}

TEST(CheckCloseWithZeroEpsilonWorksForSameNumber)
{
    CHECK ( CheckClose(0.1f, 0.1f, 0));
}

TEST(CheckCloseWithNaNFails)
{
    union
    {
        unsigned int bitpattern;
        float nan;
    };
    bitpattern = 0xFFFFFFFF;
    CHECK(false == CheckClose(3.0f, nan, 0.1f));
}

TEST(CheckCloseWithNaNAgainstItselfFails)
{
    union
    {
        unsigned int bitpattern;
        float nan;
    };
    bitpattern = 0xFFFFFFFF;
    CHECK(false == CheckClose(nan, nan, 0.1f));
}

TEST(CheckArrayEqualTrue)
{
    int const array[3] = { 1, 2, 3 };
    CHECK(CheckArrayEqual(array, array, 3));
}

TEST(CheckArrayEqualFalse)
{
    int const array1[3] = { 1, 2, 3 };
    int const array2[3] = { 1, 2, 2 };
    CHECK(false == CheckArrayEqual(array1, array2, 3));
}

TEST(CheckArrayCloseTrue)
{
    float const array1[3] = { 1.0f, 1.5f, 2.0f };
    float const array2[3] = { 1.01f, 1.51f, 2.01f };
    CHECK(CheckArrayClose(array1, array2, 3, 0.02f));
}

TEST(CheckArrayCloseFalse)
{
    float const array1[3] = { 1.0f, 1.5f, 2.0f };
    float const array2[3] = { 1.01f, 1.51f, 2.01f };
    CHECK(false == CheckArrayClose(array1, array2, 3, 0.001f));
}

TEST(CheckEqualsWithStringsFailsOnDifferentStrings)
{
    char txt1[] = "Hello";
    char txt2[] = "Hallo";
    TestResults results;
    CheckEqual(results, txt1, txt2, "", "", 0);
    CHECK_EQUAL (1, results.GetFailureCount());
}

char txt1[] = "Hello"; // non-const on purpose so no folding of duplicate data
char txt2[] = "Hello";

TEST(CheckEqualsWithStringsWorksOnContentsNonConstNonConst)
{
    char const* const p1 = txt1;
    char const* const p2 = txt2;
    TestResults results;
    CheckEqual(results, p1, p2, "", "", 0);
    CHECK_EQUAL (0, results.GetFailureCount());
}

TEST(CheckEqualsWithStringsWorksOnContentsConstConst)
{
    char* const p1 = txt1;
    char* const p2 = txt2;
    TestResults results;
    CheckEqual(results, p1, p2, "", "", 0);
    CHECK_EQUAL (0, results.GetFailureCount());
}

TEST(CheckEqualsWithStringsWorksOnContentsNonConstConst)
{
    char* const p1 = txt1;
    char const* const p2 = txt2;
    TestResults results;
    CheckEqual(results, p1, p2, "", "", 0);
    CHECK_EQUAL (0, results.GetFailureCount());
}

TEST(CheckEqualsWithStringsWorksOnContentsConstNonConst)
{
    char const* const p1 = txt1;
    char* const p2 = txt2;
    TestResults results;
    CheckEqual(results, p1, p2, "", "", 0);
    CHECK_EQUAL (0, results.GetFailureCount());
}

TEST(CheckEqualsWithStringsWorksOnContentsWithALiteral)
{
    char const* const p1 = txt1;
    TestResults results;
    CheckEqual(results, "Hello", p1, "", "", 0);
    CHECK_EQUAL (0, results.GetFailureCount());
}

}

