#ifndef SIGNAL_TRANSLATOR_H
#define SIGNAL_TRANSLATOR_H

#include <signal.h>


namespace UnitTest {

class SignalTranslator
{
public:
    SignalTranslator(int signal);
    ~SignalTranslator();

private:
    int m_signal;
    struct sigaction m_oldAction;
};

}

#endif

