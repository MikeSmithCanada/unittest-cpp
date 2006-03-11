#ifndef UNITTEST_TIMEHELPERS_H
#define UNITTEST_TIMEHELPERS_H

namespace UnitTest {

class ScopedTimer
{
public:
    ScopedTimer();
    int GetTimeInMs() const;    

private:
};


namespace TimeHelpers
{
void SleepMs (int ms);
}


}



#endif
