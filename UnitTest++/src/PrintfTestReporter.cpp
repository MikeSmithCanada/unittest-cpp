#include "PrintfTestReporter.h"

#include <cstdio>

namespace UnitTest
{

void PrintfTestReporter::ReportFailure(char const* file, int const line, 
                char const* testName, char const* failure)
{
    printf("%s(%d): Failure in %s: %s\n", file, line, testName, failure);
}

void PrintfTestReporter::ReportSingleResult(const std::string& /*testName*/, bool /*failed*/)
{
    //empty
}

void PrintfTestReporter::ReportSummary(int const testCount, int const failureCount, float secondsElapsed)
{
    printf("%d tests run.\n", testCount);
    printf("%d tests failed.\n", failureCount);
    printf("Test time: %.2f seconds.\n", secondsElapsed);
}

}

