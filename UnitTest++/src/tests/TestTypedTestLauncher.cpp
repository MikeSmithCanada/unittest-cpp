#include "../UnitTest++.h"
#include "../TestReporter.h"

using namespace UnitTest;

namespace
{

class MockTest : public Test
{
public:
    MockTest() 
    {
        ++instantiationCount;
    }

    static int instantiationCount;

private:
    virtual void RunImpl(TestResults&) {}
};

int MockTest::instantiationCount = 0;


TEST (TypedTestCreatorMakesTestOfCorrectType)
{
    TestLauncher* listHead = 0;
    TypedTestLauncher< MockTest > mockLauncher(&listHead, "", 0, "");

    TestResults results;
    mockLauncher.Launch(results);
    CHECK_EQUAL(1, MockTest::instantiationCount);
}
}

