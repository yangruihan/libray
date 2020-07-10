#include "log.h"

#define MAX_CALLBACKS 32

typedef struct
{
    log_log_fn fn;
    void* udata;
    int level;
} callback;

static struct
{
    void* udata;
    log_lock_fn lock;
    int level;
    bool quiet;
    callback callbacks[MAX_CALLBACKS];
} l;


static const char* level_strings[] =
{
    "TRACE", "DEBUG", "INFO", "WARN", "ERROR", "FATAL"
};

#ifdef LOG_USE_COLOR
static const char *level_colors[] =
{
  "\x1b[94m", "\x1b[36m", "\x1b[32m", "\x1b[33m", "\x1b[31m", "\x1b[35m"
};
#endif

static void stdout_callback(log_event* ev)
{
    char buf[16];
    buf[strftime(buf, sizeof(buf), "%H:%M:%S", ev->time)] = '\0';
#ifdef LOG_USE_COLOR
  fprintf(
    ev->udata, "%s %s%-5s\x1b[0m \x1b[90m%s:%d:\x1b[0m ",
    buf, level_colors[ev->level], level_strings[ev->level],
    ev->file, ev->line);
#else
    fprintf(
        ev->udata, "%s %-5s %s:%d: ",
        buf, level_strings[ev->level], ev->file, ev->line);
#endif
    vfprintf(ev->udata, ev->fmt, ev->ap);
    fprintf(ev->udata, "\n");
    fflush(ev->udata);
}

static void file_callback(log_event* ev)
{
    char buf[64];
    buf[strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", ev->time)] = '\0';
    fprintf(
        ev->udata, "%s %-5s %s:%d: ",
        buf, level_strings[ev->level], ev->file, ev->line);
    vfprintf(ev->udata, ev->fmt, ev->ap);
    fprintf(ev->udata, "\n");
    fflush(ev->udata);
}

static void lock(void)
{
    if (l.lock) { l.lock(true, l.udata); }
}

static void unlock(void)
{
    if (l.lock) { l.lock(false, l.udata); }
}

const char* log_level_string(const int level)
{
    return level_strings[level];
}

void log_set_lock(const log_lock_fn fn, void* udata)
{
    l.lock = fn;
    l.udata = udata;
}

void log_set_level(const int level)
{
    l.level = level;
}

void log_set_quiet(const bool enable)
{
    l.quiet = enable;
}

int log_add_callback(log_log_fn fn, void* udata, int level)
{
    for (int i = 0; i < MAX_CALLBACKS; i++)
    {
        if (!l.callbacks[i].fn)
        {
            l.callbacks[i] = (callback) {fn, udata, level};
            return 0;
        }
    }
    return -1;
}

int log_add_fp(FILE* fp, const int level)
{
    return log_add_callback(file_callback, fp, level);
}

static void init_event(log_event* ev, void* udata)
{
    if (!ev->time)
    {
        time_t t = time(NULL);
        ev->time = localtime(&t);
    }
    ev->udata = udata;
}

void log_log(const int level, const char* file, const int line, const char* fmt, ...)
{
    log_event ev = {
        .fmt = fmt,
        .file = file,
        .line = line,
        .level = level,
    };

    lock();

    if (!l.quiet && level >= l.level)
    {
        init_event(&ev, stderr);
        va_start(ev.ap, fmt);
        stdout_callback(&ev);
        va_end(ev.ap);
    }

    for (int i = 0; i < MAX_CALLBACKS && l.callbacks[i].fn; i++)
    {
        callback* cb = &l.callbacks[i];
        if (level >= cb->level)
        {
            init_event(&ev, cb->udata);
            va_start(ev.ap, fmt);
            cb->fn(&ev);
            va_end(ev.ap);
        }
    }

    unlock();
}
