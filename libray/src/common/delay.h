#ifndef LIBRAY_DELAY_H_
#define LIBRAY_DELAY_H_

#include <SDL_timer.h>

void ray_sleep(const unsigned int ms)
{
    SDL_Delay(ms);
}

#endif