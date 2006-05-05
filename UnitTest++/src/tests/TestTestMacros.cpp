#include "../UnitTest++.h"
#include "../TestMacros.h"
#include "../TestList.h"
#include "../TestResults.h"
#include "../TestReporter.h"
#include "RecordingReporter.h"

using namespace UnitTest;

namespace {

TestList list1;
TEST_EX(DummyTest, DefaultSuite, list1)
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
TEST_FIXTURE_EX(ThrowingThingie,DummyTestName,DefaultSuite,list2)
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

struct DummyFixture
{
    int x;
};

// We're really testing the macros so we just want them to compile and link
TEST_SUITE(SimilarlyNamedTestsInDifferentSuitesWork,TestSuite1)
{
    (void)testResults_;
}
TEST_SUITE(SimilarlyNamedTestsInDifferentSuitesWork,TestSuite2)
{
    (void)testResults_;
}

TEST_FIXTURE_SUITE(DummyFixture,SimilarlyNamedFixtureTestsInDifferentSuitesWork,TestSuite1)
{
    (void)testResults_;
}
TEST_FIXTURE_SUITE(DummyFixture,SimilarlyNamedFixtureTestsInDifferentSuitesWork,TestSuite2)
{
    (void)testResults_;
}

TestList macroTestList1;
TEST_EX(MacroTestHelper1,DefaultSuite,macroTestList1)
{
    (void)testResults_;
}

TEST(TestAddedWithTEST_EXMacroGetsDefaultSuite)
{
    CHECK(macroTestList1.GetHead() != NULL);
    CHECK_EQUAL ("MacroTestHelper1", macroTestList1.GetHead()->m_testName);
    CHECK_EQUAL ("DefaultSuite", macroTestList1.GetHead()->m_suiteName);
}

TestList macroTestList2;
TEST_FIXTURE_EX(DummyFixture,MacroTestHelper2,DefaultSuite,macroTestList2)
{
    (void)testResults_;
}

TEST(TestAddedWithTEST_FIXTURE_EXMacroGetsDefaultSuite)
{
    CHECK(macroTestList2.GetHead() != NULL);
    CHECK_EQUAL ("MacroTestHelper2", macroTestList2.GetHead()->m_testName);
    CHECK_EQUAL ("DefaultSuite", macroTestList2.GetHead()->m_suiteName);
}


}


