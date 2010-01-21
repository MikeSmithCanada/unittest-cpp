#ifndef UNITTEST_LEAK_DETECTOR
#define UNITTEST_LEAK_DETECTOR

#include "Config.h"

#if defined(UNITTEST_WINDOWS) || defined(UNITTEST_INTEL)
#include <crtdbg.h>
#endif

namespace UnitTest
{
#if defined(UNITTEST_WINDOWS) || defined(UNITTEST_INTEL)
	class LeakDetector
	{
	private:
		_CrtMemState originalMemoryState;

	public:
		LeakDetector();
		bool IsLeakDetected();
		~LeakDetector();
	};

	// Add elifs to implement leak checking for other platforms.
#else
	class LeakDetector
	{
	public:
		inline LeakDetector() {}
		inline bool IsLeakDetected() { return false; }
		inline ~LeakDetector() {}
	};
#endif
}

#endif