#include "../UnitTest++.h"
#include "../TimeConstraint.h"
#include "../TestResults.h"
#include "../TimeHelpers.h"
#include "RecordingReporter.h"

using namespace UnitTest;

namespace
{

TEST (TimeConstraintSucceedsWithFastTest)
{
    TestResults result;
    {
        TimeConstraint const t(200, result, "", 0, m_details);
        TimeHelpers::SleepMs(5);
    }
    CHECK_EQUAL (0, result.GetFailureCount());
}

TEST (TimeConstraintFailsWithSlowTest)
{
    TestResults result;
    TestDetails const details("testname", "suitename", "filename", 10);
    {
        TimeConstraint const t(10, result, "", 0, details);
        TimeHelpers::SleepMs(20);
    }
    CHECK_EQUAL (1, result.GetFailureCount());
}

TEST (TimeConstraintFailureIncludesCorrectData)
{
    RecordingReporter reporter;
    TestResults result(&reporter);
    TestDetails const details("testname", "suitename", "filename", 10);
    {
        TimeConstraint const t(10, result, "filename", 123, details);
        TimeHelpers::SleepMs(20);
    }
    CHECK (std::strstr(reporter.lastFailedFile, "filename"));
    CHECK_EQUAL (123, reporter.lastFailedLine);
    CHECK (std::strstr(reporter.lastFailedTest, "testname"));
}

TEST (TimeConstraintFailureIncludesTimeoutInformation)
{
    RecordingReporter reporter;
    TestResults result(&reporter);
    TestDetails const details("testname", "suitename", "filename", 10);
    {
        TimeConstraint const t(10, result, "", 0, details);
        TimeHelpers::SleepMs(20);
    }
    CHECK (std::strstr(reporter.lastFailedMessage, "ime constraint"));
    CHECK (std::strstr(reporter.lastFailedMessage, "under 10ms"));
}

TEST (TimeConstraintMacroUsesCorrectInfo)
{
    int testLine = 0;
    RecordingReporter reporter;
    {
        UnitTest::TestResults testResults_(&reporter);
        UNITTEST_TIME_CONSTRAINT(10);   testLine = __LINE__;
        TimeHelpers::SleepMs(20);
    }
    CHECK_EQUAL (1, reporter.testFailedCount);
    CHECK (std::strstr(reporter.lastFailedFile, __FILE__));
    CHECK_EQUAL (testLine, reporter.lastFailedLine);
    CHECK (std::strstr(reporter.lastFailedTest, "TimeConstraintMacroUsesCorrectInfo"));
}

}
