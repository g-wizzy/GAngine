#pragma once

#include <SDL2/SDL.h>

#include "input.h"

class GAngine
{
private:
    const short MS_PER_UPATE = 16;

    Input input;

    SDL_Window* window;
    SDL_Renderer* renderer;

    bool init();
    void clean_up();

    int game_loop();
    void read_input();
    void update();
    void render(double frame_advance);

    bool running;

public:
    GAngine();
    ~GAngine();

    int run();
};