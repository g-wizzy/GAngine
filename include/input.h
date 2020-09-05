#pragma once

#include <SDL2/SDL.h>

#include <map>

class Input
{
private:
    Input() {}

    std::map<SDL_Keycode, bool> keys;

public:
    static Input& get_instance();

    Input(Input const&) = delete;
    void operator=(Input const&) = delete;


    void on_event(const SDL_Event& event);
    bool is_key_down(SDL_Keycode key);
};