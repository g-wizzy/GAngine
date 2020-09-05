#pragma once

#include "systems/system.h"

#include "components.h"

#include <vector>
#include <map>

namespace ga_system
{    
    class DebugRender : public RenderSystem
    {
        private:
            std::vector<
                std::map<component::Type, component::Component*>
                > entities;

        public:
            DebugRender(SDL_Renderer* renderer) :
                RenderSystem(renderer)
                {}

            void update() override;
            
            void add_entity(
                component::Color*,
                component::Size*,
                component::Position*
                );
            void try_remove_entity(Entity const&) override;

    };
};
