#include "../UnitTest++.h"

#include "../TestReporter.h"

class CrashingTest : public UnitTest::Test
{
public:
	virtual void RunImpl(UnitTest::TestResults&)
	{
		reinterpret_cast< void (*)() >(0)();
	}
};

struct MockTestReporter : public UnitTest::TestReporter
{
public:
	virtual void ReportFailure(char const*, int, std::string) {}
	virtual void ReportSingleResult(const std::string&, bool) {}
	virtual void ReportSummary(int, int) {}
};

TEST(CrashingTestsAreReportedAsFailures)
{
	CrashingTest crashingTest;
	MockTestReporter reporter;
	UnitTest::TestResults results(reporter);

	crashingTest.Run(results);
	CHECK(results.Failed());
}

