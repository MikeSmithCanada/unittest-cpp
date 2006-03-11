#ifndef TEST_RUNNER_H
#define TEST_RUNNER_H


namespace UnitTest
{
class TestReporter;
class TestList;

class TestRunner
{
public:
    TestRunner();

    int RunAllTests(TestReporter& reporter, const TestList& list);
    
    float GetSecondsElapsed() const;
    
private:
    float m_secondsElapsed;
};


int DefaultRun();


}

#endif

