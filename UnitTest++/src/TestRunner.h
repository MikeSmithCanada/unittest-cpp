#ifndef TEST_RUNNER_H
#define TEST_RUNNER_H


namespace UnitTest
{
class TestLauncher;
class TestReporter;

class TestRunner
{
public:
    TestRunner();
    void SetTestLauncherListHead(TestLauncher** listHead);

    int RunAllTests(TestReporter& reporter);

private:
    TestLauncher** m_testLauncherListHead;
};


int DefaultRun();


}

#endif

