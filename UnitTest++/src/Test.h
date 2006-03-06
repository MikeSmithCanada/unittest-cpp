#ifndef TEST_H
#define TEST_H


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
    static Test* s_listTail;

protected:
    Test(char const* testName, char const* filename, int lineNumber);

    char const* const m_testName;

private:
    virtual void RunImpl(TestResults& testResults_) = 0;

    char const* const m_filename;
    int const m_lineNumber;

    // revoked
    Test(Test const&);
    Test& operator =(Test const&);
};



class TestRegistrar
{
public:
    TestRegistrar(Test*& listHead, Test *& listTail, Test* test);
};



}

#endif

