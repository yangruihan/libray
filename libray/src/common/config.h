#ifndef LIBRAY_CONFIG_H_
#define LIBRAY_CONFIG_H_

#include "platform.h"

// DLL
#ifdef LIBRAY_PLATFORM_WINDOWS
    #ifdef LIBRAY_DYNAMIC_LINK
        #ifdef LIBRAY_BUILD
            #define LIBRAY_API __declspec(dllexport)
        #else
            #define LIBRAY_API __declspec(dllimport)
        #endif
    #else
    #endif
#else
    #define LIBRAY_API extern
#endif

#endif // LIBRAY_CONFIG_H_