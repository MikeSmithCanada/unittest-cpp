#ifndef TEST_RUNNER_H
#define TEST_RUNNER_H


namespace UnitTest
{
class TestReporter;
class TestList;

class TestRunner
{
public:
    int RunAllTests(TestReporter& reporter, const TestList& list);
};


int DefaultRun();


}

#endif

