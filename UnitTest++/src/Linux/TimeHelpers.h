#ifndef TIMEHELPERS_H
#define TIMEHELPERS_H

#include <sys/time.h>

namespace UnitTest {

class ScopedTimer
{
public:
    ScopedTimer();
    int GetTimeInMs() const;    

private:
    struct timeval m_startTime;    
};


int GetTimeInMs();

namespace TimeHelpers
{
void SleepMs (int ms);
}


}

#endif
