#ifndef TEST_RUNNER_H
#define TEST_RUNNER_H


namespace UnitTest
{
class TestReporter;
class Test;

class TestRunner
{
public:
    int RunAllTests(TestReporter& reporter, Test* testListHead);
};


int DefaultRun();


}

#endif

