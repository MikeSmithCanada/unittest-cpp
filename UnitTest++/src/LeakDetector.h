#ifndef UNITTEST_LEAK_DETECTOR
#define UNITTEST_LEAK_DETECTOR

#include "Config.h"

#if defined(UNITTEST_WINDOWS) || defined(UNITTEST_INTEL)
#include <crtdbg.h>
#endif

namespace UnitTest
{
	class LeakDetector
	{
	private:
        #if defined(UNITTEST_WINDOWS) || defined(UNITTEST_INTEL)
		_CrtMemState originalMemoryState;
        #endif

	public:
		LeakDetector();
		bool IsLeakDetected();
		~LeakDetector();
	};
}

#endif
