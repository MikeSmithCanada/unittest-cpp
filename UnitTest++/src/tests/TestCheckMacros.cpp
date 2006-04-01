#include "../UnitTest++.h"
#include "RecordingReporter.h"


namespace {

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

    CHECK_EQUAL (m_testName, reporter.lastFailedTest);
}

TEST(CheckFailureIncludesCheckContents)
{
    RecordingReporter reporter;
    {
        UnitTest::TestResults testResults_(&reporter);
        const bool yaddayadda = false;
        CHECK (yaddayadda);
    }

    CHECK (std::strstr(reporter.lastFailedMessage, "yaddayadda"));
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

    CHECK (std::strstr(reporter.lastFailedMessage, "ThrowingFunction() == 1"));
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

TEST(CheckEqualFailureContainsCorrectInfo)
{
    int line = 0;
    RecordingReporter reporter;
    {
        UnitTest::TestResults testResults_(&reporter);
        CHECK_EQUAL (1, 123);    line = __LINE__;
    }

    CHECK_EQUAL ("CheckEqualFailureContainsCorrectInfo", reporter.lastFailedTest);
    CHECK_EQUAL (__FILE__, reporter.lastFailedFile);
    CHECK_EQUAL (line, reporter.lastFailedLine);
}

TEST(CheckEqualFailureBecauseOfExceptionIncludesCheckContents)
{
    RecordingReporter reporter;
    {
        UnitTest::TestResults testResults_(&reporter);
        CHECK_EQUAL (ThrowingFunction(), 123);
    }

    CHECK (std::strstr(reporter.lastFailedMessage, "ThrowingFunction()"));
    CHECK (std::strstr(reporter.lastFailedMessage, "123"));
}

int g_sideEffect = 0;
int FunctionWithSideEffects()
{
    ++g_sideEffect;
    return 1;
}

TEST(CheckEqualDoesNotHaveSideEffectsWhenPassing)
{
    g_sideEffect = 0;
    {
        UnitTest::TestResults testResults_;
        CHECK_EQUAL (1, FunctionWithSideEffects());
    }
    CHECK_EQUAL (1, g_sideEffect);
}

TEST(CheckEqualDoesNotHaveSideEffectsWhenFailing)
{
    g_sideEffect = 0;
    {
        UnitTest::TestResults testResults_;
        CHECK_EQUAL (2, FunctionWithSideEffects());
    }
    CHECK_EQUAL (1, g_sideEffect);
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

TEST(CheckCloseFailureContainsCorrectInfo)
{
    int line = 0;
    RecordingReporter reporter;
    {
        UnitTest::TestResults testResults_(&reporter);
        CHECK_CLOSE (1.0f, 1.1f, 0.01f);    line = __LINE__;
    }

    CHECK_EQUAL ("CheckCloseFailureContainsCorrectInfo", reporter.lastFailedTest);
    CHECK_EQUAL (__FILE__, reporter.lastFailedFile);
    CHECK_EQUAL (line, reporter.lastFailedLine);
}

TEST(CheckCloseFailureBecauseOfExceptionIncludesCheckContents)
{
    RecordingReporter reporter;
    {
        UnitTest::TestResults testResults_(&reporter);
        CHECK_CLOSE ((float)ThrowingFunction(), 1.0001f, 0.1f);
    }

    CHECK (std::strstr(reporter.lastFailedMessage, "(float)ThrowingFunction()"));
    CHECK (std::strstr(reporter.lastFailedMessage, "1.0001f"));
}

TEST(CheckCloseDoesNotHaveSideEffectsWhenPassing)
{
    g_sideEffect = 0;
    {
        UnitTest::TestResults testResults_;
        CHECK_CLOSE (1, FunctionWithSideEffects(), 0.1f);
    }
    CHECK_EQUAL (1, g_sideEffect);
}

TEST(CheckCloseDoesNotHaveSideEffectsWhenFailing)
{
    g_sideEffect = 0;
    {
        UnitTest::TestResults testResults_;
        CHECK_CLOSE (2, FunctionWithSideEffects(), 0.1f);
    }
    CHECK_EQUAL (1, g_sideEffect);
}


class ThrowingObject
{
public:
    float operator[](int) const
    {
        throw "Test throw";
    }
};

float const* FunctionWithSideEffects2()
{
    ++g_sideEffect;
    static float const data[] = {1,2,3,4};
    return data;
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
        int const data1[4] = { 0, 1, 2, 3 };
        int const data2[4] = { 0, 1, 3, 3 };
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
        int const data1[4] = { 0, 1, 2, 3 };
        int const data2[4] = { 0, 1, 3, 3 };
        CHECK_ARRAY_CLOSE (data1, data2, 4, 0.01f);
    }

    CHECK (std::strstr(reporter.lastFailedMessage, "xpected [ 0 1 2 3 ]"));
    CHECK (std::strstr(reporter.lastFailedMessage, "was [ 0 1 3 3 ]"));
}

TEST(CheckArrayCloseFailureContainsCorrectInfo)
{
    int line = 0;
    RecordingReporter reporter;
    {
        UnitTest::TestResults testResults_(&reporter);
        int const data1[4] = { 0, 1, 2, 3 };
        int const data2[4] = { 0, 1, 3, 3 };
        CHECK_ARRAY_CLOSE (data1, data2, 4, 0.01f);     line = __LINE__;
    }

    CHECK_EQUAL ("CheckArrayCloseFailureContainsCorrectInfo", reporter.lastFailedTest);
    CHECK_EQUAL (__FILE__, reporter.lastFailedFile);
    CHECK_EQUAL (line, reporter.lastFailedLine);
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

    CHECK (std::strstr(reporter.lastFailedMessage, "0.01"));
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

    CHECK (std::strstr(reporter.lastFailedMessage, "data"));
    CHECK (std::strstr(reporter.lastFailedMessage, "obj"));
}

TEST(CheckArrayCloseDoesNotHaveSideEffectsWhenPassing)
{
    g_sideEffect = 0;
    {
        UnitTest::TestResults testResults_;
        const float data[] = { 0, 1, 2, 3 };
        CHECK_ARRAY_CLOSE (data, FunctionWithSideEffects2(), 4, 0.01f);
    }
    CHECK_EQUAL (1, g_sideEffect);
}

TEST(CheckArrayCloseDoesNotHaveSideEffectsWhenFailing)
{
    g_sideEffect = 0;
    {
        UnitTest::TestResults testResults_;
        const float data[] = { 0, 1, 3, 3 };
        CHECK_ARRAY_CLOSE (data, FunctionWithSideEffects2(), 4, 0.01f);
    }
    CHECK_EQUAL (1, g_sideEffect);
}


}
