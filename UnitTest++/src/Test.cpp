#include "Config.h"
#include "Test.h"
#include "TestList.h"
#include "TestResults.h"
#include "AssertException.h"
#include "MemoryOutStream.h"
#include "ExecuteTest.h"
#include "LeakDetector.h"

#ifdef UNITTEST_POSIX
    #include "Posix/SignalTranslator.h"
#endif

namespace UnitTest {

TestList& Test::GetTestList()
{
    static TestList s_list;
    return s_list;
}

Test::Test(char const* testName, char const* suiteName, char const* filename, int lineNumber)
    : m_details(testName, suiteName, filename, lineNumber)
    , next(0)
    , m_timeConstraintExempt(false)
{
}

Test::~Test()
{
}

void Test::Run()
{
	CurrentTest::Details() = &m_details;

	LeakDetector memoryLeakChecker;

 	ExecuteTest(*this, m_details);

	if(memoryLeakChecker.IsLeakDetected())
		CurrentTest::Results()->OnTestFailure(m_details, "Memory Leak Detected!");
}

void Test::RunImpl() const
{
}

}
