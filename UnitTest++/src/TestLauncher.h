#ifndef TEST_LAUNCHER_H
#define TEST_LAUNCHER_H

#include "Test.h"

namespace UnitTest
{
class TestResults;
class TestRegistry;

class TestLauncher
{
public:
    TestLauncher(TestLauncher** listHead, Test* test);
    void Launch(TestResults& results_) const;

    TestLauncher const* GetNext() const;
    
    static TestLauncher** GetHeadAddr();    
    static TestLauncher* s_listHead;    
        
private:    
    TestLauncher const* m_next;
    Test* m_test;

    
    // revoked
    TestLauncher();
    TestLauncher(TestLauncher const&);
    TestLauncher& operator =(TestLauncher const&);    
};



}

#endif

