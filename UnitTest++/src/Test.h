#ifndef UNITTEST_TEST_H
#define UNITTEST_TEST_H

#include "TestList.h"


namespace UnitTest
{
class TestResults;

class Test
{
public:
    Test(char const* testName, char const* filename = "", int lineNumber = 0);
    virtual ~Test();
    void Run(TestResults& testResults);

    Test* next;
    char const* const m_testName;
    
    static TestList s_list;

private:
    virtual void RunImpl(TestResults& testResults_);

    char const* const m_filename;
    int const m_lineNumber;

    // revoked
    Test(Test const&);
    Test& operator =(Test const&);
};


}

#endif

