#include "../UnitTest++.h"
#include "RecordingReporter.h"

using namespace UnitTest;


namespace {


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

TEST(CheckEqualFailureIncludesCheckExpectedAndActual)
{
    RecordingReporter reporter;
    TestResults results(&reporter);
    const int something = 2;
    CheckEqual (results, 1, something, "", "", 0);

    CHECK (std::strstr(reporter.lastFailedMessage, "xpected 1"));
    CHECK (std::strstr(reporter.lastFailedMessage, "was 2"));
}


TEST(CheckCloseTrue)
{
    TestResults results;
    CheckClose(results, 3.001f, 3.0f, 0.1f, "", "", 0);
    CHECK_EQUAL (0, results.GetFailureCount());
}

TEST(CheckCloseFalse)
{
    TestResults results;
    CheckClose(results, 3.12f, 3.0f, 0.1f, "", "", 0);
    CHECK_EQUAL (1, results.GetFailureCount());
}

TEST(CheckCloseWithZeroEpsilonWorksForSameNumber)
{
    TestResults results;
    CheckClose(results, 0.1f, 0.1f, 0, "", "", 0);
    CHECK_EQUAL (0, results.GetFailureCount());
}

TEST(CheckCloseWithNaNFails)
{
    union
    {
        unsigned int bitpattern;
        float nan;
    };
    bitpattern = 0xFFFFFFFF;
    TestResults results;
    CheckClose(results, 3.0f, nan, 0.1f, "", "", 0);
    CHECK_EQUAL (1, results.GetFailureCount());
}

TEST(CheckCloseWithNaNAgainstItselfFails)
{
    union
    {
        unsigned int bitpattern;
        float nan;
    };
    bitpattern = 0xFFFFFFFF;
    TestResults results;
    CheckClose(results, nan, nan, 0.1f, "", "", 0);
    CHECK_EQUAL (1, results.GetFailureCount());
}

TEST(CheckCloseFailureIncludesCheckExpectedAndActual)
{
    RecordingReporter reporter;
    TestResults results(&reporter);
    const float expected = 0.9f;
    const float actual = 1.1f;
    CheckClose (results, expected, actual, 0.01f, "", "", 0);

    CHECK (std::strstr(reporter.lastFailedMessage, "xpected 0.9"));
    CHECK (std::strstr(reporter.lastFailedMessage, "was 1.1"));
}

TEST(CheckCloseFailureIncludesTolerance)
{
    RecordingReporter reporter;
    TestResults results(&reporter);
    CheckClose (results, 2, 3, 0.01f, "", "", 0);

    CHECK (std::strstr(reporter.lastFailedMessage, "0.01"));
}



TEST(CheckArrayEqualTrue)
{
    TestResults results;
    int const array[3] = { 1, 2, 3 };
    CheckArrayEqual(results, array, array, 3, "", "", 0);
    CHECK_EQUAL (0, results.GetFailureCount());
}

TEST(CheckArrayEqualFalse)
{
    TestResults results;
    int const array1[3] = { 1, 2, 3 };
    int const array2[3] = { 1, 2, 2 };
    CheckArrayEqual(results, array1, array2, 3, "", "", 0);
    CHECK_EQUAL (1, results.GetFailureCount());
}

TEST(CheckArrayCloseTrue)
{
    TestResults results;
    float const array1[3] = { 1.0f, 1.5f, 2.0f };
    float const array2[3] = { 1.01f, 1.51f, 2.01f };
    CheckArrayClose(results, array1, array2, 3, 0.02f, "", "", 0);
    CHECK_EQUAL (0, results.GetFailureCount());
}

TEST(CheckArrayCloseFalse)
{
    TestResults results;
    float const array1[3] = { 1.0f, 1.5f, 2.0f };
    float const array2[3] = { 1.01f, 1.51f, 2.01f };
    CheckArrayClose(results, array1, array2, 3, 0.001f, "", "", 0);
    CHECK_EQUAL (1, results.GetFailureCount());
}


}

