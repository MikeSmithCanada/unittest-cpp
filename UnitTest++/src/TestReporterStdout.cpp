#include "TestReporterStdout.h"
#include <cstdio>

namespace UnitTest
{

void TestReporterStdout::ReportFailure(char const* file, int const line, 
                char const* testName, char const* failure)
{
#ifdef __APPLE__
    std::printf("%s:%d: error: Failure in %s: %s\n", file, line, testName, failure);
#else
    std::printf("%s(%d): error: Failure in %s: %s\n", file, line, testName, failure);
#endif
}

void TestReporterStdout::ReportTestStart(char const*)
{
}

void TestReporterStdout::ReportTestFinish(char const*, float)
{
}

// c:\noel\unittest++\src\testreporterstdout.cpp(26) : error C2144: syntax error : 'void' should be preceded by ';'

void TestReporterStdout::ReportSummary(int const testCount, int const failureCount, float secondsElapsed)
{
    if (failureCount > 0)
        std::printf("FAILURE: %d out of %d tests failed.\n", failureCount, testCount);
    else
        std::printf("Success: %d tests passed.\n", testCount);
    std::printf("Test time: %.2f seconds.\n", secondsElapsed);
}

}
