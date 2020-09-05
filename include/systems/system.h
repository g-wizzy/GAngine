#pragma once

#include "entity.h"

#include <vector>
#include <SDL2/SDL_render.h>

namespace ga_system
{
    class System
    {
    public:
        System() {}
        virtual ~System() {}

        virtual void update() = 0;

        virtual void try_remove_entity(Entity const&) = 0;
    };

    class RenderSystem : System
    {
        public:
            RenderSystem(SDL_Renderer* renderer) :
                renderer(renderer)
                {}
            virtual ~RenderSystem() {}

        protected:
            SDL_Renderer* renderer;
    };
};
