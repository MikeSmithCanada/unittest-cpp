#include "../UnitTest++.h"
#include "../TestReporter.h"


namespace {

struct RecordingReporter : public UnitTest::TestReporter
{
public:
    RecordingReporter() : lastFailedTestName(0) {}

    virtual void ReportFailure(char const*, int, const char* testName, std::string failureString) 
    {
        lastFailedTestName = testName;
        lastFailureString = failureString;
    }
    virtual void ReportSingleResult(const std::string&, bool) {}
    virtual void ReportSummary(int, int) {}

    const char* lastFailedTestName;
    std::string lastFailureString;
};


TEST(CheckSuceedsOnTrue)
{
    bool failure = true;
    {
        RecordingReporter reporter;
        UnitTest::TestResults testResults_(&reporter);
        CHECK (true);
        failure = testResults_.Failed();
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
        failure = testResults_.Failed();
    }

    CHECK (failure);
}

TEST(FailureReportsCorrectTestName)
{
    std::string failureTestName;
    {
        RecordingReporter reporter;
        UnitTest::TestResults testResults_(&reporter);
        CHECK (false);
        failureTestName = reporter.lastFailedTestName;
    }

    CHECK_EQUAL (m_testName, failureTestName);
}

TEST(CheckFailureIncludesCheckContents)
{
    std::string failureString;
    {
        RecordingReporter reporter;
        UnitTest::TestResults testResults_(&reporter);
        const bool yaddayadda = false;
        CHECK (yaddayadda);
        failureString = reporter.lastFailureString;
    }

    CHECK (failureString.find("yaddayadda") != std::string::npos );
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
        RecordingReporter reporter;
        UnitTest::TestResults testResults_(&reporter);
        CHECK (ThrowingFunction() == 1);
        failure = testResults_.Failed();
    }

    CHECK (failure);
}

TEST(CheckFailureBecauseOfExceptionIncludesCheckContents)
{
    std::string failureString;
    {
        RecordingReporter reporter;
        UnitTest::TestResults testResults_(&reporter);
        CHECK (ThrowingFunction() == 1);
        failureString = reporter.lastFailureString;
    }

    CHECK (failureString.find("ThrowingFunction() == 1") != std::string::npos );
}

TEST(CheckEqualSuceedsOnEqual)
{
    bool failure = true;
    {
        RecordingReporter reporter;
        UnitTest::TestResults testResults_(&reporter);
        CHECK_EQUAL (1, 1);
        failure = testResults_.Failed();
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
        failure = testResults_.Failed();
    }

    CHECK (failure);
}

TEST(CheckEqualFailureIncludesCheckExpectedAndActual)
{
    std::string failureString;
    {
        RecordingReporter reporter;
        UnitTest::TestResults testResults_(&reporter);
        const int something = 2;
        CHECK_EQUAL (1, something);
        failureString = reporter.lastFailureString;
    }

    CHECK (failureString.find("xpected 1") != std::string::npos );
    CHECK (failureString.find("was 2") != std::string::npos );
}

TEST(CheckEqualFailsOnException)
{
    bool failure = false;
    {
        RecordingReporter reporter;
        UnitTest::TestResults testResults_(&reporter);
        CHECK_EQUAL (ThrowingFunction(), 1);
        failure = testResults_.Failed();
    }

    CHECK (failure);
}

TEST(CheckEqualFailureBecauseOfExceptionIncludesCheckContents)
{
    std::string failureString;
    {
        RecordingReporter reporter;
        UnitTest::TestResults testResults_(&reporter);
        CHECK_EQUAL (ThrowingFunction(), 1);
        failureString = reporter.lastFailureString;
    }

    CHECK (failureString.find("ThrowingFunction()") != std::string::npos );
    CHECK (failureString.find("1") != std::string::npos );
}

TEST(CheckCloseSuceedsOnEqual)
{
    bool failure = true;
    {
        RecordingReporter reporter;
        UnitTest::TestResults testResults_(&reporter);
        CHECK_CLOSE (1.0f, 1.001f, 0.01f);
        failure = testResults_.Failed();
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
        failure = testResults_.Failed();
    }

    CHECK (failure);
}

TEST(CheckCloseFailureIncludesCheckExpectedAndActual)
{
    std::string failureString;
    {
        RecordingReporter reporter;
        UnitTest::TestResults testResults_(&reporter);
        const float expected = 0.9f;
        const float actual = 1.1f;
        CHECK_CLOSE (expected, actual, 0.01f);
        failureString = reporter.lastFailureString;
    }

    CHECK (failureString.find("xpected 0.9") != std::string::npos );
    CHECK (failureString.find("was 1.1") != std::string::npos );
}

TEST(CheckCloseFailsOnException)
{
    bool failure = false;
    {
        RecordingReporter reporter;
        UnitTest::TestResults testResults_(&reporter);
        CHECK_CLOSE ((float)ThrowingFunction(), 1.0001f, 0.1f);
        failure = testResults_.Failed();
    }

    CHECK (failure);
}

TEST(CheckCloseFailureBecauseOfExceptionIncludesCheckContents)
{
    std::string failureString;
    {
        RecordingReporter reporter;
        UnitTest::TestResults testResults_(&reporter);
        CHECK_CLOSE ((float)ThrowingFunction(), 1.0001f, 0.1f);
        failureString = reporter.lastFailureString;
    }

    CHECK (failureString.find("(float)ThrowingFunction()") != std::string::npos );
    CHECK (failureString.find("1.0001f") != std::string::npos );
}

TEST(CheckArrayEqualSuceedsOnEqual)
{
    bool failure = true;
    {
        RecordingReporter reporter;
        UnitTest::TestResults testResults_(&reporter);
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
        RecordingReporter reporter;
        UnitTest::TestResults testResults_(&reporter);
        const float data1[4] = { 0, 1, 2, 3 };
        const float data2[4] = { 0, 1, 3, 3 };
        CHECK_ARRAY_EQUAL (data1, data2, 3);
        failure = testResults_.Failed();
    }

    CHECK (failure);
}

TEST(CheckArrayEqualFailureIncludesCheckExpectedAndActual)
{
    std::string failureString;
    {
        RecordingReporter reporter;
        UnitTest::TestResults testResults_(&reporter);
        const float data1[4] = { 0, 1, 2, 3 };
        const float data2[4] = { 0, 1, 3, 3 };
        CHECK_ARRAY_EQUAL (data1, data2, 4);
        failureString = reporter.lastFailureString;
    }

    CHECK (failureString.find("xpected [ 0 1 2 3 ]") != std::string::npos );
    CHECK (failureString.find("was [ 0 1 3 3 ]") != std::string::npos );
}

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

TEST(CheckArrayEqualFailsOnException)
{
    bool failure = false;
    {
        RecordingReporter reporter;
        UnitTest::TestResults testResults_(&reporter);
        const float data[4] = { 0, 1, 2, 3 };
        ThrowingObject obj;
        CHECK_ARRAY_EQUAL (data, obj, 3);
        failure = testResults_.Failed();
    }

    CHECK (failure);
}

TEST(CheckArrayEqualFailureOnExceptionIncludesCheckContents)
{
    std::string failureString;
    {
        RecordingReporter reporter;
        UnitTest::TestResults testResults_(&reporter);
        const float data[4] = { 0, 1, 2, 3 };
        ThrowingObject obj;
        CHECK_ARRAY_EQUAL (data, obj, 3);
        failureString = reporter.lastFailureString;
    }

    CHECK (failureString.find("data") != std::string::npos );
    CHECK (failureString.find("obj") != std::string::npos );
}


TEST(CheckArrayCloseSuceedsOnEqual)
{
    bool failure = true;
    {
        RecordingReporter reporter;
        UnitTest::TestResults testResults_(&reporter);
        const float data[4] = { 0, 1, 2, 3 };
        CHECK_ARRAY_CLOSE (data, data, 4, 0.01f);
        failure = testResults_.Failed();
    }

    CHECK (!failure);
}

TEST(CheckArrayCloseFailsOnNotEqual)
{
    bool failure = false;
    {
        RecordingReporter reporter;
        UnitTest::TestResults testResults_(&reporter);
        const float data1[4] = { 0, 1, 2, 3 };
        const float data2[4] = { 0, 1, 3, 3 };
        CHECK_ARRAY_CLOSE (data1, data2, 4, 0.01f);
        failure = testResults_.Failed();
    }

    CHECK (failure);
}

TEST(CheckArrayCloseFailureIncludesCheckExpectedAndActual)
{
    std::string failureString;
    {
        RecordingReporter reporter;
        UnitTest::TestResults testResults_(&reporter);
        const float data1[4] = { 0, 1, 2, 3 };
        const float data2[4] = { 0, 1, 3, 3 };
        CHECK_ARRAY_CLOSE (data1, data2, 4, 0.01f);
        failureString = reporter.lastFailureString;
    }

    CHECK (failureString.find("xpected [ 0 1 2 3 ]") != std::string::npos );
    CHECK (failureString.find("was [ 0 1 3 3 ]") != std::string::npos );
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
        failure = testResults_.Failed();
    }

    CHECK (failure);
}

TEST(CheckArrayCloseFailureOnExceptionIncludesCheckContents)
{
    std::string failureString;
    {
        RecordingReporter reporter;
        UnitTest::TestResults testResults_(&reporter);
        const float data[4] = { 0, 1, 2, 3 };
        ThrowingObject obj;
        CHECK_ARRAY_CLOSE (data, obj, 3, 0.01f);
        failureString = reporter.lastFailureString;
    }

    CHECK (failureString.find("data") != std::string::npos );
    CHECK (failureString.find("obj") != std::string::npos );
}


}
