#include "TestLauncher.h"

namespace UnitTest
{

namespace
{
    TestLauncher* s_listHead;
}

TestLauncher::TestLauncher(TestLauncher** listHead, Test* test)
    : m_next(*listHead)    
    , m_test(test)
{
    *listHead = this;
}

void TestLauncher::Launch(TestResults& testResults_) const
{
    m_test->Run(testResults_);
}

TestLauncher** TestLauncher::GetHeadAddr()
{
    static bool initialized = false;
    if (!initialized)
    {
        s_listHead = 0;
        initialized = true;
    }

    return &s_listHead;
}

TestLauncher const* TestLauncher::GetNext() const
{
    return m_next;
}

}

