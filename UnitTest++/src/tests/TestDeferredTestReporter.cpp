#include "../UnitTest++.h"
#include "../DeferredTestReporter.h"

#include <string>

namespace UnitTest
{

struct MockDeferredTestReporter : public DeferredTestReporter
{
	virtual void ReportSummary(int, int, float) 
	{
	}
};

struct DeferredTestReporterFixture
{
	DeferredTestReporterFixture()
		: testName("UniqueTestName")
		, testSuite("UniqueTestSuite")
		, details(testName.c_str(), testSuite.c_str())
	{
	}

	MockDeferredTestReporter reporter;
	std::string const testName;
	std::string const testSuite;
	TestDetails const details;
};

TEST_FIXTURE(DeferredTestReporterFixture, ReportTestStartCreatesANewDeferredTest)
{
	reporter.ReportTestStart(details);
	CHECK_EQUAL(1, (int)reporter.GetResults().size());
}

TEST_FIXTURE(DeferredTestReporterFixture, ReportTestStartCapturesTestNameAndSuite)
{
	reporter.ReportTestStart(details);

	DeferredTestResult const& result = reporter.GetResults().at(0);
	CHECK_EQUAL(testName.c_str(), result.testName);
	CHECK_EQUAL(testSuite.c_str(), result.suiteName);
}

TEST_FIXTURE(DeferredTestReporterFixture, ReportTestEndCapturesTestTime)
{
	float const elapsed = 123.45f;
	reporter.ReportTestStart(details);
	reporter.ReportTestFinish(details, elapsed);

	DeferredTestResult const& result = reporter.GetResults().at(0);
	CHECK_CLOSE(elapsed, result.timeElapsed, 0.0001f);
}

TEST_FIXTURE(DeferredTestReporterFixture, ReportFailureSavesFailureDetails)
{
	char const* filename = "filename";
	int const lineNumber = 12345;
	char const* failure = "failure";

	reporter.ReportTestStart(details);
	reporter.ReportFailure(details, filename, lineNumber, failure);

	DeferredTestResult const& result = reporter.GetResults().at(0);
	CHECK(result.failed == true);
	CHECK_EQUAL(filename, result.failureFile);
	CHECK_EQUAL(lineNumber, result.failureLine);
	CHECK_EQUAL(failure, result.failureMessage);
}

}
