#include "DeferredTestResult.h"

#include <cstdlib>

namespace UnitTest
{

DeferredTestResult::DeferredTestResult()
	: suiteName("")
	, testName("")
	, failureFile("")
	, failureMessage("")
	, failureLine(0)
	, timeElapsed(0.0f)
	, failed(false)
{
}

DeferredTestResult::DeferredTestResult(char const* suite, char const* test)
	: suiteName(suite)
	, testName(test)
	, failureFile("")
	, failureMessage("")
	, failureLine(0)
	, timeElapsed(0.0f)
	, failed(false)
{
}

}
