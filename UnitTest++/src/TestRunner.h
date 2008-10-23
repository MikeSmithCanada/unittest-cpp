#ifndef UNITTEST_TESTRUNNER_H
#define UNITTEST_TESTRUNNER_H

#include "Test.h"
#include "TestList.h"

namespace UnitTest {

class TestReporter;
class TestResults;
class Timer;

int RunAllTests();

struct True
{
	bool operator()(const Test* const) const
	{
		return true;	
	}
};

class TestRunner
{
public:
	explicit TestRunner(TestReporter& reporter);
	~TestRunner();

	template <class Predicate>
	int RunAllTestsIf(TestList const& list, char const* suiteName, 
					  const Predicate& predicate, int maxTestTimeInMs) const
	{
	    Test* curTest = list.GetHead();

	    while (curTest != 0)
	    {
		    if (IsTestInSuite(curTest,suiteName) && predicate(curTest))
				RunTest(m_result, curTest, maxTestTimeInMs);

			curTest = curTest->next;
	    }

	    return Finish();
	}	

	
private:
	TestReporter* m_reporter;
	TestResults* m_result;
	Timer* m_timer;
	bool m_ownReporter;

	int Finish() const;
	bool IsTestInSuite(Test* const curTest, char const* suiteName) const;
	void RunTest(TestResults* const result, Test* const curTest, int const maxTestTimeInMs) const;
};

}

#endif
