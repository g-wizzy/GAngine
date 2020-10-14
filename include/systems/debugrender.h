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

            component::Transform* camera;

        public:
            DebugRender() :
                RenderSystem() {}

            void update() override;
            
            void set_camera(
                component::Transform*
            );
            void add_visible(
                component::Transform*,
                component::Color*
                );
            void try_remove_entity(Entity const&) override;

    };
};
