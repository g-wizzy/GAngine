#pragma once

#include <SDL2/SDL.h>

#include "input.h"
#include "systems.h"
#include "entitymanager.h"

class GAngine
{
private:
    const short MS_PER_UPATE = 16;

    SDL_Window* window;
    SDL_Renderer* renderer;

    bool init();
    void clean_up();
    bool running;

    int game_loop();
    void handle_events();
    void update();
    void render(double frame_advance);

    ga_system::Speed* speedSystem;
    ga_system::DebugRender* debugRender;

    void create_entities();

public:
    GAngine();
    ~GAngine();

    int run();

    SDL_Renderer* get_renderer() {return renderer;}
};