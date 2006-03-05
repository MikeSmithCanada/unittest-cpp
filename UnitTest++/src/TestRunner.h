#ifndef TEST_RUNNER_H
#define TEST_RUNNER_H


namespace UnitTest
{
class TestLauncher;
class TestReporter;

class TestRunner
{
public:
    TestRunner(TestReporter& reporter);

    void SetTestLauncherListHead(TestLauncher** listHead);

    int RunAllTests();

private:
    TestReporter& m_testReporter;
    TestLauncher** m_testLauncherListHead;
};


int Run();


}

#endif

