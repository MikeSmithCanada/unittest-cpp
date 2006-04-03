#ifndef UNITTEST_CONFIG_H
#define UNITTEST_CONFIG_H

// Standard defines documented here: http://predef.sourceforge.net

#if defined _MSC_VER
    #define UNITTEST_VISUALSTUDIO

    #ifndef _DEBUG
        #pragma warning(disable:4702)  // bogus unreachable code in release mode
    #endif

#endif


#if defined(unix) || defined(__unix__) || defined(__unix) || defined(linux) || \
    defined(__APPLE__) || defined (__NetBSD__) || defined (__OpenBSD__) || defined (__FreeBSD__)
    #define UNITTEST_POSIX
#endif


#endif
