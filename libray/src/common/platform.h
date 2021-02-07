#ifndef LIBRAY_PLATFORM_H_
#define LIBRAY_PLATFORM_H_

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
    //define something for Windows (32-bit and 64-bit, this part is common)
    #define LIBRAY_PLATFORM_WINDOWS
    #ifdef _WIN64
        #define LIBRAY_PLATFORM_WINDOWS_64
    #else
        #define LIBRAY_PLATFORM_WINDOWS_32
    #endif
#elif __APPLE__
    #define LIBRAY_PLATFORM_APPLE
    #include <TargetConditionals.h>
    #if TARGET_IPHONE_SIMULATOR
        #define LIBRAY_PLATFORM_IPHONE_SIMULATOR
    #elif TARGET_OS_IPHONE
        #define LIBRAY_PLATFORM_IPHONE
    #elif TARGET_OS_MAC
        #define LIBRAY_PLATFORM_MACOS
    #else
        #error "Unknown Apple platform"
    #endif
#elif __linux__
    #define LIBRAY_PLATFORM_LINUX
#elif __unix__ // all unices not caught above
    #define LIBRAY_PLATFORM_UNIX
#elif defined(_POSIX_VERSION)
    #define LIBRAY_PLATFORM_POSIX
#else
    #error "Unknown compiler"
#endif

#endif // LIBRAY_PLATFORM_H_