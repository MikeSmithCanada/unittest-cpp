#ifndef UnitTest_CHECKS_H
#define UnitTest_CHECKS_H

#include "Config.h"

#include <sstream>

namespace UnitTest
{
	template< typename Value >
	bool Check(Value const value)
	{
#ifdef VISUAL_STUDIO
#	pragma warning(push)
#	pragma warning(disable:4127) // conditional expression is constant
#	pragma warning(disable:4800) // forcing value to bool true/false, performance warning
#endif
		return value;
#ifdef VISUAL_STUDIO
#	pragma warning(pop)
#endif
	}

	template< typename Value >
	bool CheckNull(Value const value)
	{
#ifdef VISUAL_STUDIO
#	pragma warning(push)
#	pragma warning(disable:4127) // conditional expression is constant
#endif
		return value == (void*)(0);
#ifdef VISUAL_STUDIO
#	pragma warning(pop)
#endif
	}

	template< typename Actual, typename Expected >
	bool CheckEqual(Actual const actual, Expected const expected)
	{
#ifdef VISUAL_STUDIO
#	pragma warning(push)
#	pragma warning(disable:4127) // conditional expression is constant
#endif
		return (actual == expected);
#ifdef VISUAL_STUDIO
#	pragma warning(pop)
#endif
	}

	template< typename Actual, typename Expected >
	bool CheckArrayEqual(Actual const actual, Expected const expected, int const count)
	{
		for (int i = 0; i < count; ++i)
		{
			if (!(actual[i] == expected[i]))
				return false;
		}

		return true;
	}

	template< typename Actual, typename Expected, typename Tolerance >
	bool CheckClose(Actual const actual, Expected const expected, Tolerance const tolerance)
	{
		double const diff = double(actual) - double(expected);
		double const doubleTolerance = double(tolerance);

		if (diff > doubleTolerance)
			return false;

		if (diff < -doubleTolerance)
			return false;

		return true;
	}

	template< typename Actual, typename Expected, typename Tolerance >
	bool CheckArrayClose(Actual const actual, Expected const expected, int const count, Tolerance const tolerance)
	{
		for (int i = 0; i < count; ++i)
		{
			if (!CheckClose(actual[i], expected[i], tolerance))
				return false;
		}

		return true;
	}

	template< typename Actual, typename Expected >
	std::string BuildFailureString(Actual const actual, Expected const expected)
	{
		std::stringstream failureStr;
		failureStr << "Expected " << expected << " but got " << actual << std::endl;
		return failureStr.str();
	}

	template< typename Actual, typename Expected >
	std::string BuildFailureString(Actual const* actual, Expected const* expected, int const count)
	{
		std::stringstream failureStr;
		int i;
		
		failureStr << "Expected [ ";

		for (i = 0; i < count; ++i)
			failureStr << expected[i] << ' ';

		failureStr << "] but got [ ";

		for (i = 0; i < count; ++i)
			failureStr << actual[i] << ' ';

		failureStr << ']' << std::endl;

        return failureStr.str();		
	}
}

#endif 

