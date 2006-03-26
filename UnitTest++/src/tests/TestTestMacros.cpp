#include "../UnitTest++.h"
#include "../TestMacros.h"
#include "../TestList.h"
#include "../TestResults.h"
#include "../TestReporter.h"
#include "RecordingReporter.h"

using namespace UnitTest;

namespace {

TestList list1;
TEST_EX(DummyTest,list1)
{
    (void)testResults_;
}

TEST (TestsAreAddedToTheListThroughMacro)
{
    CHECK (list1.GetHead() != 0);
    CHECK (list1.GetHead()->next == 0);
}

struct ThrowingThingie
{
	ThrowingThingie() : dummy(false)
    {
		if (!dummy)
	        throw "Oops";
    } 
	bool dummy;
};

TestList list2;
TEST_FIXTURE_EX(ThrowingThingie,DummyTestName,list2)
{
    (void)testResults_;
}

TEST (ExceptionsInFixtureAreReportedAsHappeningInTheFixture)
{
    RecordingReporter reporter;
    TestResults result(&reporter);
    list2.GetHead()->Run(result);
    
    CHECK (strstr(reporter.lastFailedMessage, "xception"));
    CHECK (strstr(reporter.lastFailedMessage, "fixture"));
    CHECK (strstr(reporter.lastFailedMessage, "ThrowingThingie"));
}



}


