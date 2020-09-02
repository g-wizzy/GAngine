#pragma once

#include <SDL2/SDL_events.h>

#include <map>

class Input
{
private:
    std::map<SDL_Keysym, bool> keys;

public:
    void on_event(const SDL_Event& event);

    bool is_key_down(SDL_Keysym key);
};