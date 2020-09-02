#include "input.h"

void Input::on_event(const SDL_Event& event)
{
    switch (event.type)
    {
    case SDL_KEYDOWN:
        keys.insert_or_assign(event.key.keysym.sym, true);
        break;
    
    case SDL_KEYUP:
        keys.insert_or_assign(event.key.keysym.sym, false);
        break;

    default:
        break;
    }
}

bool Input::is_key_down(SDL_Keycode key)
{
    auto iterator = keys.find(key);
    if (iterator != keys.end())
    {
        return iterator->second;
    }
    else
    {
        return false;
    }
    
}