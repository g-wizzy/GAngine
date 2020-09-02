#pragma once

class SDL_Window;
class SDL_Renderer;

namespace helper
{
    double getCurrentTime();

    int create_window(SDL_Window* window, SDL_Renderer* renderer);
}