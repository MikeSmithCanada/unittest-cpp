#include "TestReporterStdout.h"
#include <cstdio>

namespace UnitTest
{

void TestReporterStdout::ReportFailure(char const* file, int const line, 
                char const* testName, char const* failure)
{
    std::printf("%s(%d): Failure in %s: %s\n", file, line, testName, failure);
}

void TestReporterStdout::ReportTestStart(char const*)
{
    //empty
}

void TestReporterStdout::ReportSummary(int const testCount, int const failureCount, float secondsElapsed)
{
    if (failureCount > 0)
        std::printf("FAILURE: %d out of %d tests failed.\n", failureCount, testCount);
    else
        std::printf("Success: %d tests passed.\n", testCount);
    std::printf("Test time: %.2f seconds.\n", secondsElapsed);
}

}

