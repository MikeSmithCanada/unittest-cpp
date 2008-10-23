#include "TestRunner.h"
#include "TestResults.h"
#include "TestReporter.h"
#include "TestReporterStdout.h"
#include "TimeHelpers.h"
#include "MemoryOutStream.h"

#include <cstring>


namespace UnitTest {

int RunAllTests()
{
	TestRunner runner;
	return runner.RunAllTestsIf(Test::GetTestList(), NULL, True(), 0);
}

TestRunner::TestRunner()
	: m_reporter(new TestReporterStdout)
	, m_result(new TestResults(m_reporter))
	, m_timer(new Timer)
	, m_ownReporter(true)
{
	m_timer->Start();
}

TestRunner::TestRunner(TestReporter* reporter)
	: m_reporter(reporter)
	, m_result(new TestResults(reporter))
	, m_timer(new Timer)
	, m_ownReporter(false)
{
	m_timer->Start();
}

TestRunner::~TestRunner()
{
	delete m_result;
	delete m_timer;

	if (m_ownReporter)
		delete m_reporter;
}

int TestRunner::Finish() const
{
    float const secondsElapsed = m_timer->GetTimeInMs() / 1000.0f;
    m_reporter->ReportSummary(m_result->GetTotalTestCount(), 
							  m_result->GetFailedTestCount(), 
							  m_result->GetFailureCount(), 
							  secondsElapsed);
    
	 return m_result->GetFailureCount();
}

bool TestRunner::IsTestInSuite(Test* const curTest, char const* suiteName) const
{
	return (suiteName == NULL) || !std::strcmp(curTest->m_details.suiteName, suiteName);
}

void TestRunner::RunTest(TestResults* const result, Test* const curTest, int const maxTestTimeInMs) const
{
	Timer testTimer;
	testTimer.Start();
	result->OnTestStart(curTest->m_details);
	
	curTest->Run(*result);
 
	int const testTimeInMs = testTimer.GetTimeInMs();
	if (maxTestTimeInMs > 0 && testTimeInMs > maxTestTimeInMs && !curTest->m_timeConstraintExempt)
	{
	    MemoryOutStream stream;
	    stream << "Global time constraint failed. Expected under " << maxTestTimeInMs <<
	            "ms but took " << testTimeInMs << "ms.";

	    result->OnTestFailure(curTest->m_details, stream.GetText());
	}

	result->OnTestFinish(curTest->m_details, testTimeInMs/1000.0f);
}

}
