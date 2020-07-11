#include "timer.h"

#include <malloc.h>

#include "common/delay.h"
#include "common/module.h"

timer* ray_get_timer()
{
    module* m = module_get(ray_mt_timer);
    if (!m)
    {
        m = (module*)timer_create();
        module_set(ray_mt_timer, m);
    }
    return (timer*)m;
}

timer* timer_create()
{
    timer* t = (timer*)malloc(sizeof(timer));
    t->base.module_type = ray_mt_timer;
    t->base.module_name = "timer";

    t->fps = 0;
    t->average_delta = 0;
    t->fps_update_frequency = 1;
    t->frames = 0;
    t->delta_time = 0;

    t->prev_fps_update = t->curr_time = timer_get_time();

    return t;
}

void timer_destroy(timer* timer)
{
    free(timer);
}

double timer_step(timer* t)
{
    t->frames++;

    t->prev_time = t->curr_time;
    t->curr_time = timer_get_time();

    t->delta_time = t->curr_time - t->prev_time;

    const double time_since_last = t->curr_time - t->prev_fps_update;

    if (time_since_last > t->fps_update_frequency)
    {
        t->fps = (int)(t->frames / time_since_last + 0.5);
        t->average_delta = time_since_last / t->frames;
        t->prev_fps_update = t->curr_time;
        t->frames = 0;
    }

    return t->delta_time;
}

void timer_sleep(const double seconds)
{
    if (seconds >= 0)
        ray_sleep((unsigned int)(seconds * 1000));
}

double timer_get_delta(timer* t)
{
    return t->delta_time;
}

int timer_get_fps(timer* t)
{
    return t->fps;
}

double timer_get_average_delta(timer* t)
{
    return t->average_delta;
}

static Uint64 get_time_absolute()
{
    return SDL_GetPerformanceCounter();
}

static Uint64 get_frequency()
{
    return SDL_GetPerformanceFrequency();
}

static Uint64 freq;
static Uint64 start;
static int time_init = 0;

double timer_get_time()
{
    if (time_init == 0)
    {
        start = get_time_absolute();
        freq = get_frequency();

        time_init = 1;
    }

    const Uint64 now = get_time_absolute();
    const Uint64 rel = now - start;
    return (double)rel / (double)freq;
}
