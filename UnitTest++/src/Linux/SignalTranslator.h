#ifndef SIGNAL_TRANSLATOR_H
#define SIGNAL_TRANSLATOR_H

#include <signal.h>


namespace UnitTest {

class SignalTranslator
{
public:
    SignalTranslator();
    ~SignalTranslator();

private:
    struct sigaction m_old_SIGFPE_action;
    struct sigaction m_old_SIGTRAP_action;
    struct sigaction m_old_SIGSEGV_action;
    struct sigaction m_old_SIGBUS_action;
    struct sigaction m_old_SIGABRT_action;
    struct sigaction m_old_SIGALRM_action;
};

}

#endif

