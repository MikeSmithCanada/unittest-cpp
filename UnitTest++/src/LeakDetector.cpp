#include "Config.h"
#include "LeakDetector.h"

#if defined(UNITTEST_WINDOWS) || defined(UNITTEST_INTEL)

namespace UnitTest
{
	LeakDetector::LeakDetector()
	{
		_CrtMemCheckpoint(&originalMemoryState);
	}

// Fucking VS10...
#pragma warning(push)
#pragma warning(disable:4101)
	bool LeakDetector::IsLeakDetected()
	{
		_CrtMemState newState;
		_CrtMemState temp;
		_CrtMemCheckpoint(&newState);

		return !!_CrtMemDifference(&temp, &originalMemoryState, &newState);
	}

	LeakDetector::~LeakDetector()
	{
	}
}
#pragma warning(pop)

// Feel free to add special-case code for other platforms in a seperate #elif
// block. the #else is just for general case code for unsupported platforms.
#else

namespace UnitTest
{
	LeakDetector::LeakDetector()
	{
	}

	bool LeakDetector::IsLeakDetected()
	{
		return false;
	}

	LeakDetector::~LeakDetector()
	{
	}
}

#endif