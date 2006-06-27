#include "Checks.h"
#include <cstring>

namespace UnitTest {

namespace {

void CheckStringsEqual(TestResults& results, char const* const expected, char const* const actual,
                TestDetails const& details, char const* const filename, int const line)
{
    if (std::strcmp(expected, actual))
    {
        UnitTest::MemoryOutStream stream;
        stream << "Expected " << expected << " but was " << actual;

        results.OnTestFailure(details, filename, line, stream.GetText());
    }
}

}


void CheckEqual(TestResults& results, char const* const expected, char const* const actual,
                TestDetails const& details, char const* const filename, int const line)
{
    CheckStringsEqual(results, expected, actual, details, filename, line);
}

void CheckEqual(TestResults& results, char* const expected, char* const actual,
                TestDetails const& details, char const* const filename, int const line)
{
    CheckStringsEqual(results, expected, actual, details, filename, line);
}

void CheckEqual(TestResults& results, char* const expected, char const* const actual,
                TestDetails const& details, char const* const filename, int const line)
{
    CheckStringsEqual(results, expected, actual, details, filename, line);
}

void CheckEqual(TestResults& results, char const* const expected, char* const actual,
                TestDetails const& details, char const* const filename, int const line)
{
    CheckStringsEqual(results, expected, actual, details, filename, line);
}


}
