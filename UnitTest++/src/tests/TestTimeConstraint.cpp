#include "../UnitTest++.h"
#include "../TestResults.h"
#include "../TimeHelpers.h"
#include "RecordingReporter.h"
#include "ScopedCurrentTest.h"

using namespace UnitTest;

namespace
{

TEST(TimeConstraintSucceedsWithFastTest)
{
    TestResults result;
    {
		ScopedCurrentTest scopedResult(result);
        TimeConstraint t(200, TestDetails("", "", "", 0));
        TimeHelpers::SleepMs(5);
    }
    CHECK_EQUAL(0, result.GetFailureCount());
}

TEST(TimeConstraintFailsWithSlowTest)
{
    TestResults result;
    {
		ScopedCurrentTest scopedResult(result);
        TimeConstraint t(10, TestDetails("", "", "", 0));
        TimeHelpers::SleepMs(20);
    }
    CHECK_EQUAL(1, result.GetFailureCount());
}

TEST(TimeConstraintFailureIncludesCorrectData)
{
    RecordingReporter reporter;
    TestResults result(&reporter);
    {
		ScopedCurrentTest scopedResult(result);

		TestDetails const details("testname", "suitename", "filename", 10);
        TimeConstraint t(10, details);
        TimeHelpers::SleepMs(20);
    }

	CHECK(std::strstr(reporter.lastFailedFile, "filename"));
    CHECK_EQUAL(10, reporter.lastFailedLine);
    CHECK(std::strstr(reporter.lastFailedTest, "testname"));
}

TEST(TimeConstraintFailureIncludesTimeoutInformation)
{
    RecordingReporter reporter;
    TestResults result(&reporter);
    {
		ScopedCurrentTest scopedResult(result);
        TimeConstraint t(10, TestDetails("", "", "", 0));
        TimeHelpers::SleepMs(20);
    }

	CHECK(std::strstr(reporter.lastFailedMessage, "ime constraint"));
    CHECK(std::strstr(reporter.lastFailedMessage, "under 10ms"));
}

}
