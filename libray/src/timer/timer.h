#ifndef LIBRAY_TIMER_H_
#define LIBRAY_TIMER_H_

#include "common/module.h"

typedef struct
{
    module base;

    double curr_time;
    double prev_time;
    double prev_fps_update;
    int fps;
    double average_delta;
    double fps_update_frequency;
    int frames;
    double delta_time;
} timer;

timer* ray_get_timer();

timer* timer_create();
void   timer_destroy(timer* timer);

double timer_step(timer* t);
void   timer_sleep(double seconds);
double timer_get_delta(timer* t);
int    timer_get_fps(timer* t);
double timer_get_average_delta(timer* t);
double timer_get_time();

#endif // LIBRAY_TIMER_H_
