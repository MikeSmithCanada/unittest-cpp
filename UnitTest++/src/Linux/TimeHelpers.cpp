#include "TimeHelpers.h"
#include <unistd.h>

namespace UnitTest {

ScopedTimer::ScopedTimer()
{
    gettimeofday(&m_startTime, 0);
}

int ScopedTimer::GetTimeInMs() const
{
    struct timeval currentTime;
    gettimeofday(&currentTime, 0);
    int const dsecs = currentTime.tv_sec - m_startTime.tv_sec;
    int const dus = currentTime.tv_usec - m_startTime.tv_usec;
    return dsecs*1000 + dus/1000;
}


void TimeHelpers::SleepMs (int ms)
{
    usleep(ms * 1000);
}

}
