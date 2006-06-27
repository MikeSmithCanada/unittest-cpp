#include "../UnitTest++.h"
#include "RecordingReporter.h"

using namespace UnitTest;


namespace {


TEST(CheckEqualWithUnsignedLong)
{
    TestResults results;
    unsigned long something = 2;
    CHECK_EQUAL( something, something );
}

TEST(CheckEqualsWithStringsFailsOnDifferentStrings)
{
    char txt1[] = "Hello";
    char txt2[] = "Hallo";
    TestResults results;
	TestDetails details("");
    CheckEqual(results, txt1, txt2, details, "", 0);
    CHECK_EQUAL (1, results.GetFailureCount());
}

char txt1[] = "Hello"; // non-const on purpose so no folding of duplicate data
char txt2[] = "Hello";

TEST(CheckEqualsWithStringsWorksOnContentsNonConstNonConst)
{
    char const* const p1 = txt1;
    char const* const p2 = txt2;
    TestResults results;
	TestDetails details("");
    CheckEqual(results, p1, p2, details, "", 0);
    CHECK_EQUAL (0, results.GetFailureCount());
}

TEST(CheckEqualsWithStringsWorksOnContentsConstConst)
{
    char* const p1 = txt1;
    char* const p2 = txt2;
    TestResults results;
	TestDetails details("");
    CheckEqual(results, p1, p2, details, "", 0);
    CHECK_EQUAL (0, results.GetFailureCount());
}

TEST(CheckEqualsWithStringsWorksOnContentsNonConstConst)
{
    char* const p1 = txt1;
    char const* const p2 = txt2;
    TestResults results;
	TestDetails details("");
    CheckEqual(results, p1, p2, details, "", 0);
    CHECK_EQUAL (0, results.GetFailureCount());
}

TEST(CheckEqualsWithStringsWorksOnContentsConstNonConst)
{
    char const* const p1 = txt1;
    char* const p2 = txt2;
    TestResults results;
	TestDetails details("");
    CheckEqual(results, p1, p2, details, "", 0);
    CHECK_EQUAL (0, results.GetFailureCount());
}

TEST(CheckEqualsWithStringsWorksOnContentsWithALiteral)
{
    char const* const p1 = txt1;
    TestResults results;
	TestDetails details("");
    CheckEqual(results, "Hello", p1, details, "", 0);
    CHECK_EQUAL (0, results.GetFailureCount());
}

TEST(CheckEqualFailureIncludesCheckExpectedAndActual)
{
    RecordingReporter reporter;
    TestResults results(&reporter);
	TestDetails details("");
    const int something = 2;
    CheckEqual (results, 1, something, details, "", 0);

    CHECK (std::strstr(reporter.lastFailedMessage, "xpected 1"));
    CHECK (std::strstr(reporter.lastFailedMessage, "was 2"));
}

TEST(CheckEqualFailureIncludesDetails)
{
    RecordingReporter reporter;
    TestResults results(&reporter);
    TestDetails details("mytest", "mysuite", "", -1);

    CheckEqual (results, 1, 2, details, "file.h", 101);

    CHECK_EQUAL("mytest", reporter.lastFailedTest);
    CHECK_EQUAL("mysuite", reporter.lastFailedSuite);
    CHECK_EQUAL("file.h", reporter.lastFailedFile);
    CHECK_EQUAL(101, reporter.lastFailedLine);
}

TEST(CheckCloseTrue)
{
    TestResults results;
	TestDetails details("");
    CheckClose(results, 3.001f, 3.0f, 0.1f, details, "", 0);
    CHECK_EQUAL (0, results.GetFailureCount());
}

TEST(CheckCloseFalse)
{
    TestResults results;
	TestDetails details("");
    CheckClose(results, 3.12f, 3.0f, 0.1f, details, "", 0);
    CHECK_EQUAL (1, results.GetFailureCount());
}

TEST(CheckCloseWithZeroEpsilonWorksForSameNumber)
{
    TestResults results;
	TestDetails details("");
    CheckClose(results, 0.1f, 0.1f, 0, details, "", 0);
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
	TestDetails details("");
    CheckClose(results, 3.0f, nan, 0.1f, details, "", 0);
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
	TestDetails details("");
    CheckClose(results, nan, nan, 0.1f, details, "", 0);
    CHECK_EQUAL (1, results.GetFailureCount());
}

TEST(CheckCloseFailureIncludesCheckExpectedAndActual)
{
    RecordingReporter reporter;
    TestResults results(&reporter);
    const float expected = 0.9f;
    const float actual = 1.1f;
	TestDetails details("");
    CheckClose (results, expected, actual, 0.01f, details, "", 0);

    CHECK (std::strstr(reporter.lastFailedMessage, "xpected 0.9"));
    CHECK (std::strstr(reporter.lastFailedMessage, "was 1.1"));
}

TEST(CheckCloseFailureIncludesTolerance)
{
    RecordingReporter reporter;
    TestResults results(&reporter);
	TestDetails details("");
    CheckClose (results, 2, 3, 0.01f, details, "", 0);

    CHECK (std::strstr(reporter.lastFailedMessage, "0.01"));
}

TEST(CheckCloseFailureIncludesDetails)
{
    RecordingReporter reporter;
    TestResults results(&reporter);
    TestDetails details("mytest", "mysuite", "", -1);

    CheckClose (results, 2, 3, 0.01f, details, "header.h", 10);

    CHECK_EQUAL("mytest", reporter.lastFailedTest);
    CHECK_EQUAL("mysuite", reporter.lastFailedSuite);
    CHECK_EQUAL("header.h", reporter.lastFailedFile);
    CHECK_EQUAL(10, reporter.lastFailedLine);
}


TEST(CheckArrayEqualTrue)
{
    TestResults results;
	TestDetails details("");

	int const array[3] = { 1, 2, 3 };
    CheckArrayEqual(results, array, array, 3, details, "", 0);
    CHECK_EQUAL (0, results.GetFailureCount());
}

TEST(CheckArrayEqualFalse)
{
    TestResults results;
	TestDetails details("");

	int const array1[3] = { 1, 2, 3 };
    int const array2[3] = { 1, 2, 2 };
    CheckArrayEqual(results, array1, array2, 3, details, "", 0);
    CHECK_EQUAL (1, results.GetFailureCount());
}

TEST(CheckArrayCloseTrue)
{
    TestResults results;
	TestDetails details("");

	float const array1[3] = { 1.0f, 1.5f, 2.0f };
    float const array2[3] = { 1.01f, 1.51f, 2.01f };
    CheckArrayClose(results, array1, array2, 3, 0.02f, details, "", 0);
    CHECK_EQUAL (0, results.GetFailureCount());
}

TEST(CheckArrayCloseFalse)
{
    TestResults results;
	TestDetails details("");

	float const array1[3] = { 1.0f, 1.5f, 2.0f };
    float const array2[3] = { 1.01f, 1.51f, 2.01f };
    CheckArrayClose(results, array1, array2, 3, 0.001f, details, "", 0);
    CHECK_EQUAL (1, results.GetFailureCount());
}

TEST(CheckArrayCloseFailureIncludesDetails)
{
    RecordingReporter reporter;
    TestResults results(&reporter);
    TestDetails details("arrayCloseTest", "arrayCloseSuite", "", -1);

    float const array1[3] = { 1.0f, 1.5f, 2.0f };
    float const array2[3] = { 1.01f, 1.51f, 2.01f };
    CheckArrayClose(results, array1, array2, 3, 0.001f, details, "file", 1337);

    CHECK_EQUAL("arrayCloseTest", reporter.lastFailedTest);
    CHECK_EQUAL("arrayCloseSuite", reporter.lastFailedSuite);
    CHECK_EQUAL("file", reporter.lastFailedFile);
    CHECK_EQUAL(1337, reporter.lastFailedLine);
}


TEST(CheckArray2DCloseTrue)
{
    TestResults results;
	TestDetails details("");

	float const array1[3][3] = { { 1.0f, 1.5f, 2.0f },
                                 { 2.0f, 2.5f, 3.0f },
                                 { 3.0f, 3.5f, 4.0f } };
    float const array2[3][3] = { { 1.01f, 1.51f, 2.01f },
                                 { 2.01f, 2.51f, 3.01f },
                                 { 3.01f, 3.51f, 4.01f } };
    CheckArray2DClose(results, array1, array2, 3, 3, 0.02f, details, "", 0);
    CHECK_EQUAL (0, results.GetFailureCount());
}

TEST(CheckArray2DCloseFalse)
{
    TestResults results;
	TestDetails details("");

	float const array1[3][3] = { { 1.0f, 1.5f, 2.0f },
                                 { 2.0f, 2.5f, 3.0f },
                                 { 3.0f, 3.5f, 4.0f } };
    float const array2[3][3] = { { 1.01f, 1.51f, 2.01f },
                                 { 2.01f, 2.51f, 3.01f },
                                 { 3.01f, 3.51f, 4.01f } };
    CheckArray2DClose(results, array1, array2, 3, 3, 0.001f, details, "", 0);
    CHECK_EQUAL (1, results.GetFailureCount());
}

TEST(CheckCloseWithDoublesSucceeds)
{
	CHECK_CLOSE(0.5, 0.5, 0.0001);
}

TEST(CheckArray2DCloseFailureIncludesDetails)
{
    RecordingReporter reporter;
    TestResults results(&reporter);
    TestDetails details("array2DCloseTest", "array2DCloseSuite", "", -1);

    float const array1[3][3] = { { 1.0f, 1.5f, 2.0f },
                                 { 2.0f, 2.5f, 3.0f },
                                 { 3.0f, 3.5f, 4.0f } };
    float const array2[3][3] = { { 1.01f, 1.51f, 2.01f },
                                 { 2.01f, 2.51f, 3.01f },
                                 { 3.01f, 3.51f, 4.01f } };
    CheckArray2DClose(results, array1, array2, 3, 3, 0.001f, details, "file", 1234);

    CHECK_EQUAL("array2DCloseTest", reporter.lastFailedTest);
    CHECK_EQUAL("array2DCloseSuite", reporter.lastFailedSuite);
    CHECK_EQUAL("file", reporter.lastFailedFile);
    CHECK_EQUAL(1234, reporter.lastFailedLine);
}

}
