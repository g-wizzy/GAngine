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

    speedSystem = new ga_system::Speed();
    debugRender = new ga_system::DebugRender(renderer);
    create_entities();

    int errcode = game_loop();

    clean_up();

    return errcode;
}


void GAngine::create_entities()
{
    EntityManager& em = EntityManager::get_instance();

    em.begin_new();
        component::Color* color = static_cast<component::Color*>(em.add_component(component::color)); // defaults to white
        component::Size* size = static_cast<component::Size*>(em.add_component(component::size));
        size->w = size->h = 50;
        component::Position* pos = static_cast<component::Position*>(em.add_component(component::position));
        pos->x = 20;
        component::Speed* speed = static_cast<component::Speed*>(em.add_component(component::speed));
        speed->dx = 5;
        speed->dy = 5;
    Entity& entity = em.end_new();

    debugRender->add_entity(color, size, pos);
    speedSystem->add_entity(speed, pos);
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

        handle_events();
        while (lag > MS_PER_UPATE)
        {
            update();
            lag -= MS_PER_UPATE;
        }
        render(lag / MS_PER_UPATE);
    }

    return 0;
}


void GAngine::handle_events()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            running = false;
            break;

        // TODO: add read more events (resize, lose / gain focus, etc.)

        default:
            Input::get_instance().on_event(event);
        }
    }
}


void GAngine::update()
{
    if (Input::get_instance().is_key_down(SDLK_ESCAPE))
    {
        running = false;
    }

    speedSystem->update();
}

#include <iostream>
void GAngine::render(double frame_advance)
{
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderClear(renderer);

    debugRender->update();
    
    SDL_RenderPresent(renderer);
}