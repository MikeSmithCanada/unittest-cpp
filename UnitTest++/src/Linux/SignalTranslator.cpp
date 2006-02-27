#include "SignalTranslator.h"

#include <setjmp.h>

namespace UnitTest {

namespace {

sigjmp_buf g_jmpPnt;

void SignalHandler(int signum)
{
    siglongjmp(g_jmpPnt, signum);
}

}


SignalTranslator::SignalTranslator(const int signal)
    : m_signal (signal)
{
    struct sigaction act;
    act.sa_handler = SignalHandler;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;

    sigaction(m_signal, &act, &m_oldAction);

    if (sigsetjmp(g_jmpPnt, 1) != 0)
        throw "Unhandled system exception";
}

SignalTranslator::~SignalTranslator()
{
    sigaction(m_signal, &m_oldAction, 0);
}


}
