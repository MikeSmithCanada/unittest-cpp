#ifndef UnitTest_CHECKS_H
#define UnitTest_CHECKS_H

#include "Config.h"
#include <sstream>


namespace UnitTest
{
#ifdef VISUAL_STUDIO
#   pragma warning(push)
#   pragma warning(disable:4127) // conditional expression is constant
#   pragma warning(disable:4800) // forcing value to bool true/false, performance warning
#endif
    template< typename Value >
    bool Check(Value const value)
    {
        return value;
    }

    template< typename Value >
    bool CheckNull(Value const value)
    {
        return value == (void*)(0);
    }

    template< typename Expected, typename Actual >
    bool CheckEqual(Expected const expected, Actual const actual)
    {
        return (expected == actual);
    }
#ifdef VISUAL_STUDIO
#   pragma warning(pop)
#endif
    

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
    bool CheckClose(Expected const expected, Actual const actual, Tolerance const tolerance)
    {
        double const diff = double(actual) - double(expected);
        double const doubleTolerance = double(tolerance);

        if (diff > -doubleTolerance && diff < doubleTolerance)
            return true;

        return false;
    }

    template< typename Expected, typename Actual, typename Tolerance >
    bool CheckArrayClose(Expected const expected, Actual const actual, int const count, Tolerance const tolerance)
    {
        for (int i = 0; i < count; ++i)
        {
            if (!CheckClose(expected[i], actual[i], tolerance))
                return false;
        }

        return true;
    }

    template< typename Expected, typename Actual>
    std::string BuildFailureString(Expected const expected, Actual const actual)
    {
        std::stringstream failureStr;
        failureStr << "Expected " << expected << " but was " << actual;
        return failureStr.str();
    }

    template< typename Expected, typename Actual >
    std::string BuildFailureString(Expected const* expected, Actual const* actual, int const count)
    {
        std::stringstream failureStr;
        int i;

        failureStr << "Expected [ ";

        for (i = 0; i < count; ++i)
            failureStr << expected[i] << ' ';

        failureStr << "] but was [ ";

        for (i = 0; i < count; ++i)
            failureStr << actual[i] << ' ';

        failureStr << ']';

        return failureStr.str();
    }
}

#endif 

