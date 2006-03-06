#ifndef TEST_RUNNER_H
#define TEST_RUNNER_H


namespace UnitTest
{
class TestLauncher;
class TestReporter;

class TestRunner
{
public:
    int RunAllTests(TestReporter& reporter, TestLauncher* launcherListHead);
};


int DefaultRun();


}

#endif

