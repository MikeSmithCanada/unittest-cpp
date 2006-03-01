#include "PrintfTestReporter.h"

#include <cstdio>

namespace UnitTest
{

void PrintfTestReporter::ReportFailure(char const* file, int const line, 
                const char* testName, std::string const failure)
{
    printf("%s(%d): Failure in %s: %s\n", file, line, testName, failure.c_str());
}

void PrintfTestReporter::ReportSingleResult(const std::string& /*testName*/, bool /*failed*/)
{
    //empty
}

void PrintfTestReporter::ReportSummary(int const testCount, int const failureCount)
{
    printf("%d tests run.\n", testCount);
    printf("%d failures.\n", failureCount);
}

}

