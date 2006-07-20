#include "TestReporterStdout.h"
#include <cstdio>

#include "TestDetails.h"

namespace UnitTest {

void TestReporterStdout::ReportFailure(TestDetails const& details, char const* failure)
{
#ifdef __APPLE__
    char const* const errorFormat = "%s:%d: error: Failure in %s: %s\n";
#else
    char const* const errorFormat = "%s(%d): error: Failure in %s: %s\n";
#endif
    std::printf(errorFormat, details.filename, details.lineNumber, details.testName, failure);
}

void TestReporterStdout::ReportTestStart(TestDetails const& /*test*/)
{
}

void TestReporterStdout::ReportTestFinish(TestDetails const& /*test*/, float)
{
}

void TestReporterStdout::ReportSummary(int const totalTestCount, int const failureCount, float secondsElapsed)
{
    if (failureCount > 0)
        std::printf("FAILURE: %d out of %d tests failed.\n", failureCount, totalTestCount);
    else
        std::printf("Success: %d tests passed.\n", totalTestCount);
    std::printf("Test time: %.2f seconds.\n", secondsElapsed);
}

}
