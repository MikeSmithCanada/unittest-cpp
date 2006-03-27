#include "Config.h"

#if defined POSIX
    #include "Posix/TimeHelpers.h"
#else
    #include "Win32/TimeHelpers.h"
#endif
