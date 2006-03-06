#include "TestLauncher.h"

namespace UnitTest
{

TestLauncher* TestLauncher::s_listHead = 0;

TestLauncher::TestLauncher(TestLauncher*& listHead, Test* test)
    : m_next(listHead)    
    , m_test(test)
{
    listHead = this;
}

void TestLauncher::Launch(TestResults& testResults_) const
{
    m_test->Run(testResults_);
}

TestLauncher const* TestLauncher::GetNext() const
{
    return m_next;
}

}

