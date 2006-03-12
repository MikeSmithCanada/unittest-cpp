#include "../UnitTest++.h"
#include "../TestMacros.h"
#include "../TestList.h"
#include "../TestResults.h"
#include "../TestReporter.h"

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


struct RecordingReporter : public UnitTest::TestReporter
{
public:
    RecordingReporter() : lastFailedTestName(0) {}

    virtual void ReportFailure(char const*, int, char const* testName, char const* failureString) 
    {
        lastFailedTestName = testName;
        lastFailureString = failureString;
    }
    virtual void ReportTestStart(char const*) {}
    virtual void ReportSummary(int, int, float) {}

    const char* lastFailedTestName;
    const char* lastFailureString;
};


struct ThrowingThingie
{
    ThrowingThingie()
    {
        throw "Oops";
    }
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
    
    CHECK (strstr(reporter.lastFailureString, "xception"));
    CHECK (strstr(reporter.lastFailureString, "fixture"));
    CHECK (strstr(reporter.lastFailureString, "ThrowingThingie"));
}



}


