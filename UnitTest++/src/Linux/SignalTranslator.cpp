#include "SignalTranslator.h"
#include <setjmp.h>

namespace UnitTest {

namespace {

sigjmp_buf g_sigMark;

void SignalHandler (int sig)
{
    siglongjmp(g_sigMark, sig );
}

}


SignalTranslator::SignalTranslator ()
{
    struct sigaction action;
    action.sa_flags = 0;
    action.sa_handler = SignalHandler;
    sigemptyset( &action.sa_mask );

    sigaction( SIGSEGV, &action, &m_old_SIGSEGV_action );
    sigaction( SIGFPE , &action, &m_old_SIGFPE_action  );
    sigaction( SIGTRAP, &action, &m_old_SIGTRAP_action );
    sigaction( SIGBUS , &action, &m_old_SIGBUS_action  );
    //sigaction( SIGABRT, &action, &m_old_SIGABRT_action );

    if (sigsetjmp( g_sigMark, 1 ) != 0)
        throw ("Unhandled system exception");
}

SignalTranslator::~SignalTranslator()
{
    //sigaction( SIGABRT, &m_old_SIGABRT_action, 0 );
    sigaction( SIGBUS , &m_old_SIGBUS_action , 0 );
    sigaction( SIGTRAP, &m_old_SIGTRAP_action, 0 );
    sigaction( SIGFPE , &m_old_SIGFPE_action , 0 );
    sigaction( SIGSEGV, &m_old_SIGSEGV_action, 0 );

}

}
