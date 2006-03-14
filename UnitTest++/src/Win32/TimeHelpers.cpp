#include "TimeHelpers.h"

#include <windows.h>
#include <cassert>

namespace UnitTest {

Timer::Timer()
{
	BOOL const success = ::QueryPerformanceFrequency(reinterpret_cast< LARGE_INTEGER* >(&m_frequency));
	assert(success);
	(void) success;
}

void Timer::Start()
{
	BOOL const success = ::QueryPerformanceCounter(reinterpret_cast< LARGE_INTEGER* >(&m_startTime));
	assert(success);
	(void) success;
}

int Timer::GetTimeInMs() const
{
	LARGE_INTEGER curTime;
	BOOL const success = ::QueryPerformanceCounter(&curTime);
	assert(success);
	(void) success;

	LARGE_INTEGER elapsedTime;
	elapsedTime.QuadPart = curTime.QuadPart - m_startTime;

	double const seconds = double(elapsedTime.QuadPart) / double(m_frequency);

	return int(seconds * 1000.0f);
}


void TimeHelpers::SleepMs(int const ms)
{
	::Sleep(ms);
}

}
