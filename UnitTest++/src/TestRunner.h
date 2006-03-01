#ifndef TEST_RUNNER_H
#define TEST_RUNNER_H

#include "PrintfTestReporter.h"

namespace UnitTest
{
class TestLauncher;
class TestReporter;

class TestRunner
{
public:
    TestRunner();

    void SetTestReporter(TestReporter* testReporter);
    void SetTestLauncherListHead(TestLauncher** listHead);

    int RunAllTests();

private:
    TestLauncher** m_testLauncherListHead;

    TestReporter* m_testReporter;
    PrintfTestReporter m_defaultTestReporter;
};

}

#endif

