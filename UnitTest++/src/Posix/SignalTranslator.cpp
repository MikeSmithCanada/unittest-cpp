#include "SignalTranslator.h"
#include <setjmp.h>
#include <signal.h>

namespace UnitTest {

namespace {

int g_instanceCount = 0;
sigjmp_buf g_sigMark;
struct sigaction g_old_SIGFPE_action;
struct sigaction g_old_SIGTRAP_action;
struct sigaction g_old_SIGSEGV_action;
struct sigaction g_old_SIGBUS_action;
struct sigaction g_old_SIGABRT_action;
struct sigaction g_old_SIGALRM_action;


void SignalHandler (int sig)
{
    siglongjmp(g_sigMark, sig );
}


void RegisterSignals()
{
    struct sigaction action;
    action.sa_flags = 0;
    action.sa_handler = SignalHandler;
    sigemptyset( &action.sa_mask );

    sigaction( SIGSEGV, &action, &g_old_SIGSEGV_action );
    sigaction( SIGFPE , &action, &g_old_SIGFPE_action  );
    sigaction( SIGTRAP, &action, &g_old_SIGTRAP_action );
    sigaction( SIGBUS , &action, &g_old_SIGBUS_action  );
    //sigaction( SIGABRT, &action, &g_old_SIGABRT_action );

    if (sigsetjmp( g_sigMark, 1 ) != 0)
        throw ("Unhandled system exception");
}

void UnregisterSignals()
{
    //sigaction( SIGABRT, &g_old_SIGABRT_action, 0 );
    sigaction( SIGBUS , &g_old_SIGBUS_action , 0 );
    sigaction( SIGTRAP, &g_old_SIGTRAP_action, 0 );
    sigaction( SIGFPE , &g_old_SIGFPE_action , 0 );
    sigaction( SIGSEGV, &g_old_SIGSEGV_action, 0 );
}

}


SignalTranslator::SignalTranslator ()
{
    if (g_instanceCount == 0)
        RegisterSignals();
    ++g_instanceCount;
}

SignalTranslator::~SignalTranslator()
{
    --g_instanceCount;
    if (g_instanceCount == 0)
        UnregisterSignals();    
}

}
