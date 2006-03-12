#include "../UnitTest++.h"
#include "../TestReporter.h"


namespace {

struct RecordingReporter : public UnitTest::TestReporter
{
public:
    RecordingReporter() 
        : lastFailedTestName(0)
        , lastFailureString(0)
    {}

    virtual void ReportFailure(char const*, int, char const* testName, char const* failureString) 
    {
        lastFailedTestName = testName;
        lastFailureString = failureString;
    }
    virtual void ReportTestStart(char const*) {}
    virtual void ReportSummary(int, int, float) {}

    char const* lastFailedTestName;
    char const* lastFailureString;
};


TEST(CheckSuceedsOnTrue)
{
    bool failure = true;
    {
        RecordingReporter reporter;
        UnitTest::TestResults testResults_(&reporter);
        CHECK (true);
        failure = (testResults_.GetFailureCount() > 0);
    }

    CHECK (!failure);
}

TEST(CheckFailsOnFalse)
{
    bool failure = false;
    {
        RecordingReporter reporter;
        UnitTest::TestResults testResults_(&reporter);
        CHECK (false);
        failure = (testResults_.GetFailureCount() > 0);
    }

    CHECK (failure);
}

TEST(FailureReportsCorrectTestName)
{
    RecordingReporter reporter;
    {
        UnitTest::TestResults testResults_(&reporter);
        CHECK (false);
    }

    CHECK (!strcmp(m_testName, reporter.lastFailedTestName));
}

TEST(CheckFailureIncludesCheckContents)
{
    RecordingReporter reporter;
    {
        UnitTest::TestResults testResults_(&reporter);
        const bool yaddayadda = false;
        CHECK (yaddayadda);
    }

    CHECK (strstr(reporter.lastFailureString, "yaddayadda"));
}

int ThrowingFunction()
{
    throw "Doh";
}

TEST(CheckFailsOnException)
{
    bool failure = false;
    {
        RecordingReporter reporter;
        UnitTest::TestResults testResults_(&reporter);
        CHECK (ThrowingFunction() == 1);
        failure = (testResults_.GetFailureCount() > 0);
    }

    CHECK (failure);
}

TEST(CheckFailureBecauseOfExceptionIncludesCheckContents)
{
    RecordingReporter reporter;
    {
        UnitTest::TestResults testResults_(&reporter);
        CHECK (ThrowingFunction() == 1);
    }

    CHECK (strstr(reporter.lastFailureString, "ThrowingFunction() == 1"));
}

TEST(CheckEqualSuceedsOnEqual)
{
    bool failure = true;
    {
        RecordingReporter reporter;
        UnitTest::TestResults testResults_(&reporter);
        CHECK_EQUAL (1, 1);
        failure = (testResults_.GetFailureCount() > 0);
    }

    CHECK (!failure);
}

TEST(CheckEqualFailsOnNotEqual)
{
    bool failure = false;
    {
        RecordingReporter reporter;
        UnitTest::TestResults testResults_(&reporter);
        CHECK_EQUAL (1, 2);
        failure = (testResults_.GetFailureCount() > 0);
    }

    CHECK (failure);
}

TEST(CheckEqualFailureIncludesCheckExpectedAndActual)
{
    RecordingReporter reporter;
    {
        UnitTest::TestResults testResults_(&reporter);
        const int something = 2;
        CHECK_EQUAL (1, something);
    }

    CHECK (strstr(reporter.lastFailureString, "xpected 1"));
    CHECK (strstr(reporter.lastFailureString, "was 2"));
}

TEST(CheckEqualFailsOnException)
{
    bool failure = false;
    {
        RecordingReporter reporter;
        UnitTest::TestResults testResults_(&reporter);
        CHECK_EQUAL (ThrowingFunction(), 1);
        failure = (testResults_.GetFailureCount() > 0);
    }

    CHECK (failure);
}

TEST(CheckEqualFailureBecauseOfExceptionIncludesCheckContents)
{
    RecordingReporter reporter;
    {
        UnitTest::TestResults testResults_(&reporter);
        CHECK_EQUAL (ThrowingFunction(), 123);
    }

    CHECK (strstr(reporter.lastFailureString, "ThrowingFunction()"));
    CHECK (strstr(reporter.lastFailureString, "123"));
}

TEST(CheckCloseSuceedsOnEqual)
{
    bool failure = true;
    {
        RecordingReporter reporter;
        UnitTest::TestResults testResults_(&reporter);
        CHECK_CLOSE (1.0f, 1.001f, 0.01f);
        failure = (testResults_.GetFailureCount() > 0);
    }

    CHECK (!failure);
}

TEST(CheckCloseFailsOnNotEqual)
{
    bool failure = false;
    {
        RecordingReporter reporter;
        UnitTest::TestResults testResults_(&reporter);
        CHECK_CLOSE (1.0f, 1.1f, 0.01f);
        failure = (testResults_.GetFailureCount() > 0);
    }

    CHECK (failure);
}

TEST(CheckCloseFailureIncludesCheckExpectedAndActual)
{
    RecordingReporter reporter;
    {
        UnitTest::TestResults testResults_(&reporter);
        const float expected = 0.9f;
        const float actual = 1.1f;
        CHECK_CLOSE (expected, actual, 0.01f);
    }

    CHECK (strstr(reporter.lastFailureString, "xpected 0.9"));
    CHECK (strstr(reporter.lastFailureString, "was 1.1"));
}

TEST(CheckCloseFailureIncludesTolerance)
{
    RecordingReporter reporter;
    {
        UnitTest::TestResults testResults_(&reporter);
        CHECK_CLOSE (2, 3, 0.01f);
    }

    CHECK (strstr(reporter.lastFailureString, "0.01"));
}

TEST(CheckCloseFailsOnException)
{
    bool failure = false;
    {
        RecordingReporter reporter;
        UnitTest::TestResults testResults_(&reporter);
        CHECK_CLOSE ((float)ThrowingFunction(), 1.0001f, 0.1f);
        failure = (testResults_.GetFailureCount() > 0);
    }

    CHECK (failure);
}

TEST(CheckCloseFailureBecauseOfExceptionIncludesCheckContents)
{
    RecordingReporter reporter;
    {
        UnitTest::TestResults testResults_(&reporter);
        CHECK_CLOSE ((float)ThrowingFunction(), 1.0001f, 0.1f);
    }

    CHECK (strstr(reporter.lastFailureString, "(float)ThrowingFunction()"));
    CHECK (strstr(reporter.lastFailureString, "1.0001f"));
}

TEST(CheckArrayEqualSuceedsOnEqual)
{
    bool failure = true;
    {
        RecordingReporter reporter;
        UnitTest::TestResults testResults_(&reporter);
        const float data[4] = { 0, 1, 2, 3 };
        CHECK_ARRAY_EQUAL (data, data, 3);
        failure = (testResults_.GetFailureCount() > 0);
    }

    CHECK (!failure);
}

TEST(CheckArrayEqualFailsOnNotEqual)
{
    bool failure = false;
    {
        RecordingReporter reporter;
        UnitTest::TestResults testResults_(&reporter);
        const float data1[4] = { 0, 1, 2, 3 };
        const float data2[4] = { 0, 1, 3, 3 };
        CHECK_ARRAY_EQUAL (data1, data2, 3);
        failure = (testResults_.GetFailureCount() > 0);
    }

    CHECK (failure);
}

TEST(CheckArrayEqualFailureIncludesCheckExpectedAndActual)
{
    RecordingReporter reporter;
    {
        UnitTest::TestResults testResults_(&reporter);
        const float data1[4] = { 0, 1, 2, 3 };
        const float data2[4] = { 0, 1, 3, 3 };
        CHECK_ARRAY_EQUAL (data1, data2, 4);
    }

    CHECK (strstr(reporter.lastFailureString, "xpected [ 0 1 2 3 ]"));
    CHECK (strstr(reporter.lastFailureString, "was [ 0 1 3 3 ]"));
}

class ThrowingObject
{
public:
    float operator[](int) const
    {
        throw "Test throw";
    }
};

TEST(CheckArrayEqualFailsOnException)
{
    bool failure = false;
    {
        RecordingReporter reporter;
        UnitTest::TestResults testResults_(&reporter);
        const float data[4] = { 0, 1, 2, 3 };
        ThrowingObject obj;
        CHECK_ARRAY_EQUAL (data, obj, 3);
        failure = (testResults_.GetFailureCount() > 0);
    }

    CHECK (failure);
}

TEST(CheckArrayEqualFailureOnExceptionIncludesCheckContents)
{
    RecordingReporter reporter;
    {
        UnitTest::TestResults testResults_(&reporter);
        const float data[4] = { 0, 1, 2, 3 };
        ThrowingObject obj;
        CHECK_ARRAY_EQUAL (data, obj, 3);
    }

    CHECK (strstr(reporter.lastFailureString, "data"));
    CHECK (strstr(reporter.lastFailureString, "obj"));
}


TEST(CheckArrayCloseSuceedsOnEqual)
{
    bool failure = true;
    {
        RecordingReporter reporter;
        UnitTest::TestResults testResults_(&reporter);
        const float data[4] = { 0, 1, 2, 3 };
        CHECK_ARRAY_CLOSE (data, data, 4, 0.01f);
        failure = (testResults_.GetFailureCount() > 0);
    }

    CHECK (!failure);
}

TEST(CheckArrayCloseFailsOnNotEqual)
{
    bool failure = false;
    {
        RecordingReporter reporter;
        UnitTest::TestResults testResults_(&reporter);
        float const data1[4] = { 0, 1, 2, 3 };
        float const data2[4] = { 0, 1, 3, 3 };
        CHECK_ARRAY_CLOSE (data1, data2, 4, 0.01f);
        failure = (testResults_.GetFailureCount() > 0);
    }

    CHECK (failure);
}

TEST(CheckArrayCloseFailureIncludesCheckExpectedAndActual)
{
    RecordingReporter reporter;
    {
        UnitTest::TestResults testResults_(&reporter);
        float const data1[4] = { 0, 1, 2, 3 };
        float const data2[4] = { 0, 1, 3, 3 };
        CHECK_ARRAY_CLOSE (data1, data2, 4, 0.01f);
    }

    CHECK (strstr(reporter.lastFailureString, "xpected [ 0 1 2 3 ]"));
    CHECK (strstr(reporter.lastFailureString, "was [ 0 1 3 3 ]"));
}


TEST(CheckArrayCloseFailureIncludesTolerance)
{
    RecordingReporter reporter;
    {
        UnitTest::TestResults testResults_(&reporter);
        float const data1[4] = { 0, 1, 2, 3 };
        float const data2[4] = { 0, 1, 3, 3 };
        CHECK_ARRAY_CLOSE (data1, data2, 4, 0.01f);
    }

    CHECK (strstr(reporter.lastFailureString, "0.01"));
}


TEST(CheckArrayCloseFailsOnException)
{
    bool failure = false;
    {
        RecordingReporter reporter;
        UnitTest::TestResults testResults_(&reporter);
        const float data[4] = { 0, 1, 2, 3 };
        ThrowingObject obj;
        CHECK_ARRAY_CLOSE (data, obj, 3, 0.01f);
        failure = (testResults_.GetFailureCount() > 0);
    }

    CHECK (failure);
}

TEST(CheckArrayCloseFailureOnExceptionIncludesCheckContents)
{
    RecordingReporter reporter;
    {
        UnitTest::TestResults testResults_(&reporter);
        const float data[4] = { 0, 1, 2, 3 };
        ThrowingObject obj;
        CHECK_ARRAY_CLOSE (data, obj, 3, 0.01f);
    }

    CHECK (strstr(reporter.lastFailureString, "data"));
    CHECK (strstr(reporter.lastFailureString, "obj"));
}


}
