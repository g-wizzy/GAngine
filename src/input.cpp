#include "input.h"

Input& Input::get_instance()
{
    static Input instance;

    return instance;
}

void Input::on_event(const SDL_Event& event)
{
    switch (event.type)
    {
    case SDL_KEYDOWN:
        keys[event.key.keysym.sym] = true;
        break;
    
    case SDL_KEYUP:
        keys[event.key.keysym.sym] = false;
        break;

    default:
        break;
    }
}

bool Input::is_key_down(SDL_Keycode key)
{
    // If the entry is inexistent, the map will insert the default value
    // false, which is the expected behavior
    return keys[key];
}