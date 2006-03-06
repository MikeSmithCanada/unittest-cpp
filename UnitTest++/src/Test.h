#ifndef TEST_H
#define TEST_H

#include <string>

namespace UnitTest
{
class TestResults;

class Test
{
public:
    virtual ~Test();
    void Run(TestResults& testResults);

    Test* next;
    static Test* s_listHead;

protected:
    Test(std::string testName = std::string(), 
         std::string filename = std::string(), 
         int lineNumber = 0);

    std::string const m_testName;

private:
    virtual void RunImpl(TestResults& testResults_) = 0;

    std::string const m_filename;
    int const m_lineNumber;

    // revoked
    Test(Test const&);
    Test& operator =(Test const&);
};


}

#endif

