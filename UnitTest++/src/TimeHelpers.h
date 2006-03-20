#ifdef LINUX
    #include "Linux/TimeHelpers.h"
#elif defined(__APPLE__)
	#include "Darwin/TimeHelpers.h"
#else
    #include "Win32/TimeHelpers.h"
#endif
