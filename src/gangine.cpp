#include "gangine.h"

#include "input.h"
#include "helper.h"

#include <iostream>

using namespace helper;

GAngine::GAngine() :
    running(true)
{
    SDL_Init(SDL_INIT_EVERYTHING);
}

GAngine::~GAngine()
{
    SDL_Quit();
}


int GAngine::run()
{
    if (!init())
    {
        return -1;
    }

    int errcode = game_loop();

    clean_up();

    return errcode;
}


bool GAngine::init()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        std::cout << "SDL_Init error";
        return false;
    }

    window = NULL;
    renderer = NULL;

    window = SDL_CreateWindow(
        "GAngine v0.1",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        640,
        480,
        SDL_WINDOW_OPENGL
    );
    if (window == NULL)
    {
        std::cout << "SDL_CreateWindow error";
        return false;
    }

    renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED
    );
    if (renderer == NULL)
    {
        std::cout << "SDL_CreateRenderer error";
        return false;
    }

    return true;
}


void GAngine::clean_up()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}


int GAngine::game_loop()
{
    double previous = getCurrentTime();
    double lag = 0.0;

    running = true;
    while (running)
    {
        double current = getCurrentTime();
        double elapsed = current - previous;
        previous = current;
        lag += elapsed;

        read_input();
        while (lag > MS_PER_UPATE)
        {
            update();
            lag -= MS_PER_UPATE;
        }
        render(lag / MS_PER_UPATE);
    }

    return 0;
}


void GAngine::read_input()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        input.on_event(event);
    }
}


void GAngine::update()
{
    if (input.is_key_down(SDLK_ESCAPE))
    {
        running = false;
    }
}

#include <iostream>
void GAngine::render(double frame_advance)
{
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}