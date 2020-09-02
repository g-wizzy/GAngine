#include "helper.h"

#include <SDL2/SDL.h>


double helper::getCurrentTime()
{
    return SDL_GetTicks();
}


int helper::create_window(SDL_Window* window, SDL_Renderer* renderer)
{
    window = NULL;
    renderer = NULL;
    window = SDL_CreateWindow(
        "GAngine prototype",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        640,
        480,
        0
    );
    if (window == NULL)
    {
        return -1;
    }

    renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );
    if (renderer == NULL)
    {
        return -1;
    }

    return 0;
}