#include "TestLauncher.h"

namespace UnitTest
{

namespace
{
    TestLauncher* s_listHead;
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

TestLauncher::TestLauncher(TestLauncher** listHead, char const* filename, int line, char const* testName)
    : m_filename(filename)
    , m_line(line)
    , m_testName(testName)
    , m_next(*listHead)    
{
    *listHead = this;
}

TestLauncher::~TestLauncher()
{
}

TestLauncher const* TestLauncher::GetNext() const
{
    return m_next;
}

}

