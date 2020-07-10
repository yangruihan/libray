#ifndef LIBRAY_LOG_H_
#define LIBRAY_LOG_H_

#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>
#include <time.h>

typedef struct
{
    va_list ap;
    const char* fmt;
    const char* file;
    struct tm* time;
    void* udata;
    int line;
    int level;
} log_event;

typedef void (*log_log_fn)(log_event* ev);
typedef void (*log_lock_fn)(bool lock, void* udata);

enum
{
    ray_log_trace,
    ray_log_debug,
    ray_log_info,
    ray_log_warn,
    ray_log_error,
    ray_log_fatal
};

#define RAY_LOG_TRACE(...) log_log(ray_log_trace, __FILE__, __LINE__, __VA_ARGS__)
#define RAY_LOG_DEBUG(...) log_log(ray_log_debug, __FILE__, __LINE__, __VA_ARGS__)
#define RAY_LOG_INFO(...)  log_log(ray_log_info,  __FILE__, __LINE__, __VA_ARGS__)
#define RAY_LOG_WARN(...)  log_log(ray_log_warn,  __FILE__, __LINE__, __VA_ARGS__)
#define RAY_LOG_ERROR(...) log_log(ray_log_error, __FILE__, __LINE__, __VA_ARGS__)
#define RAY_LOG_FATAL(...) log_log(ray_log_fatal, __FILE__, __LINE__, __VA_ARGS__)

const char* log_level_string(int level);
void log_set_lock(log_lock_fn fn, void* udata);
void log_set_level(int level);
void log_set_quiet(bool enable);
int log_add_callback(log_log_fn fn, void* udata, int level);
int log_add_fp(FILE* fp, int level);

void log_log(int level, const char* file, int line, const char* fmt, ...);

#endif
