#ifndef LIBRAY_CONFIG_H_
#define LIBRAY_CONFIG_H_

// Platform
#if defined(WIN32) || defined(_WIN32)
    #define LIBRAY_WINDOWS 1
#endif

// DLL
#ifdef LIBRAY_WINDOWS
    #define LIBRAY_API __declspec(dllexport)
#else
    #define LIBRAY_API
#endif

#endif // LIBRAY_CONFIG_H_