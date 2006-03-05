#include "TimeHelpers.h"
#include <ctime>


int TimeHelpers::GetTimeInMs()
{

    return 0;
}

void TimeHelpers::Sleep (int ms)
{
    timespec delay;
    delay.tv_sec = 0;
    delay.tv_nsec = ms * 1000;
    nanosleep(&delay, 0);
}

