#ifndef UNITTEST_CHECKS_H
#define UNITTEST_CHECKS_H

#include "Config.h"
#include "TestResults.h"
#include "MemoryOutStream.h"

namespace UnitTest {


template< typename Value >
bool Check(Value const value)
{
    return !!value; // doing double negative to avoid silly VS warnings
}


template< typename Expected, typename Actual >
void CheckEqual(TestResults& results, Expected const expected, Actual const actual,
                TestDetails const& details, char const* const filename, int const line)
{
    if (!(expected == actual))
    {
        UnitTest::MemoryOutStream stream;
        stream << "Expected " << expected << " but was " << actual;

        results.OnTestFailure(details, filename, line, stream.GetText());
    }
}

void CheckEqual(TestResults& results, char const* expected, char const* actual,
                TestDetails const& details, char const* filename, int line);

void CheckEqual(TestResults& results, char* expected, char* actual,
                TestDetails const& details, char const* filename, int line);

void CheckEqual(TestResults& results, char* expected, char const* actual,
                TestDetails const& details, char const* filename, int line);

void CheckEqual(TestResults& results, char const* expected, char* actual,
                TestDetails const& details, char const* filename, int line);

template< typename Expected, typename Actual, typename Tolerance >
bool AreClose(Expected const expected, Actual const actual, Tolerance const tolerance)
{
    return (actual >= expected - tolerance) && (actual <= expected + tolerance);
}
                
template< typename Expected, typename Actual, typename Tolerance >
void CheckClose(TestResults& results, Expected const expected, Actual const actual, Tolerance const tolerance,
                TestDetails const& details, char const* const filename, int const line)
{
    if (!AreClose(expected, actual, tolerance))
    { 
        UnitTest::MemoryOutStream stream;
        stream << "Expected " << expected << " +/- " << tolerance << " but was " << actual;

        results.OnTestFailure(details, filename, line, stream.GetText());
    }
}


template< typename Expected, typename Actual >
void CheckArrayEqual(TestResults& results, Expected const expected, Actual const actual,
                int const count, TestDetails const& details, char const* const filename, int const line)
{
    bool equal = true;
    for (int i = 0; i < count; ++i)
        equal &= (expected[i] == actual[i]);

    if (!equal)
    {
        UnitTest::MemoryOutStream stream;
        stream << "Expected [ ";
        for (int i = 0; i < count; ++i)
            stream << expected[i] << " ";
        stream << "] but was [ ";
        for (int i = 0; i < count; ++i)
            stream << actual[i] << " ";
        stream << "]";

        results.OnTestFailure(details, filename, line, stream.GetText());
    }
}

template< typename Expected, typename Actual, typename Tolerance >
bool CheckClose2(Expected const expected, Actual const actual, Tolerance const tolerance)
{
    return ((actual >= expected - tolerance) && (actual <= expected + tolerance));
}

template< typename Expected, typename Actual, typename Tolerance >
bool ArrayAreClose(Expected const expected, Actual const actual, int const count, Tolerance const tolerance)
{
    bool equal = true;
    for (int i = 0; i < count; ++i)
        equal &= AreClose(expected[i], actual[i], tolerance);
    return equal;
}

template< typename Expected, typename Actual, typename Tolerance >
void CheckArrayClose(TestResults& results, Expected const expected, Actual const actual,
                   int const count, Tolerance const tolerance, TestDetails const& details,
                   char const* const filename, int const line)
{
    bool equal = ArrayAreClose(expected, actual, count, tolerance);

    if (!equal)
    {
        UnitTest::MemoryOutStream stream;
        stream << "Expected [ ";    
        for (int i = 0; i < count; ++i)
            stream << expected[i] << " ";
        stream << "] +/- " << tolerance << " but was [ ";
        for (int i = 0; i < count; ++i)
            stream << actual[i] << " ";
        stream << "]";

        results.OnTestFailure(details, filename, line, stream.GetText());
    }
}

template< typename Expected, typename Actual, typename Tolerance >
void CheckArray2DClose(TestResults& results, Expected const expected, Actual const actual,
                   int const rows, int const columns, Tolerance const tolerance, 
                   TestDetails const& details, char const* const filename, int const line)
{
    bool equal = true;
    for (int i = 0; i < rows; ++i)
        equal &= ArrayAreClose(expected[i], actual[i], columns, tolerance);

    if (!equal)
    {
        UnitTest::MemoryOutStream stream;
        stream << "Expected [ ";    
        for (int i = 0; i < rows; ++i)
        {
            stream << "[ ";
            for (int j = 0; j < columns; ++j)
                stream << expected[i][j] << " ";
            stream << "] ";
        }
        stream << "] +/- " << tolerance << " but was [ ";
        for (int i = 0; i < rows; ++i)
        {
            stream << "[ ";
            for (int j = 0; j < columns; ++j)
                stream << actual[i][j] << " ";
            stream << "] ";
        }
        stream << "]";
        
        results.OnTestFailure(details, filename, line, stream.GetText());
    }
}

}

#endif 
