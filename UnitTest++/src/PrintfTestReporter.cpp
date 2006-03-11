#include "PrintfTestReporter.h"

#include <cstdio>

namespace UnitTest
{

void PrintfTestReporter::ReportFailure(char const* file, int const line, 
                char const* testName, char const* failure)
{
    printf("%s(%d): Failure in %s: %s\n", file, line, testName, failure);
}

void PrintfTestReporter::ReportSingleResult(char const* /*testName*/, bool /*failed*/)
{
    //empty
}

void PrintfTestReporter::ReportSummary(int const testCount, int const failureCount, float secondsElapsed)
{
    if (failureCount > 0)
        printf("FAILURE: %d out of %d tests failed.\n", failureCount, testCount);
    else
        printf("Success: %d tests passed.\n", testCount);
    printf("Test time: %.2f seconds.\n", secondsElapsed);
}

}

