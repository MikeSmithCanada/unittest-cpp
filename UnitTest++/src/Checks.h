#ifndef UNITTEST_CHECKS_H
#define UNITTEST_CHECKS_H

#include "Config.h"
#include "TestResults.h"
#include "MemoryOutStream.h"
#include "BuildFailureString.h"

namespace UnitTest {


#ifdef UNITTEST_VISUALSTUDIO
#   pragma warning(push)
#   pragma warning(disable:4800) // forcing value to bool true/false, performance warning
#endif
template< typename Value >
bool Check(Value const value)
{
    return value;
}
#ifdef UNITTEST_VISUALSTUDIO
#   pragma warning(pop)
#endif

template< typename Value >
bool CheckNull(Value const value)
{
    return (value == (void*)(0));
}

template< typename Expected, typename Actual >
void CheckEqual(TestResults& results, Expected const expected, Actual const actual,
                char const* const testName, char const* const filename, int const line)
{
    if (!(expected == actual))
    {
        UnitTest::MemoryOutStream stream;
        stream << "Expected " << expected << " but was " << actual;
        results.OnTestFailure(filename, line, testName, stream.GetText());
    }
}

void CheckEqual(TestResults& results, char const* expected, char const* actual,
                char const* testName, char const* filename, int line);
void CheckEqual(TestResults& results, char* expected, char* actual,
                char const* testName, char const* filename, int line);
void CheckEqual(TestResults& results, char* expected, char const* actual,
                char const* testName, char const* filename, int line);
void CheckEqual(TestResults& results, char const* expected, char* actual,
                char const* testName, char const* filename, int line);

template< typename Expected, typename Actual, typename Tolerance >
void CheckClose(TestResults& results, Expected const expected, Actual const actual, Tolerance const tolerance,
                char const* const testName, char const* const filename, int const line)
{
    if (!((actual >= expected - tolerance) && (actual <= expected + tolerance)))
    { 
        UnitTest::MemoryOutStream stream;
        stream << "Expected " << expected << " +/- " << tolerance << " but was " << actual;
        results.OnTestFailure(filename, line, testName, stream.GetText());
    }
}


template< typename Expected, typename Actual >
bool CheckArrayEqual(Expected const expected, Actual const actual, int const count)
{
    for (int i = 0; i < count; ++i)
    {
        if (!(expected[i] == actual[i]))
            return false;
    }

    return true;
}

template< typename Expected, typename Actual, typename Tolerance >
bool CheckClose2(Expected const expected, Actual const actual, Tolerance const tolerance)
{
    return ((actual >= expected - tolerance) && (actual <= expected + tolerance));
}

template< typename Expected, typename Actual, typename Tolerance >
bool CheckArrayClose(Expected const expected, Actual const actual, int const count, Tolerance const tolerance)
{
    for (int i = 0; i < count; ++i)
    {
        if (!CheckClose2(expected[i], actual[i], tolerance))
            return false;
    }

    return true;
}


}


#endif 

