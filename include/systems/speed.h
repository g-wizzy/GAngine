#pragma once

#include "systems/system.h"
#include "components.h"

#include <vector>
#include <map>

namespace ga_system
{    
    class Speed : public System
    {
        private:
            std::vector<
                std::map<component::Type, component::Component*>
                > entities;

        public:
            void update() override;

            void add_entity(
                component::Speed*,
                component::Transform*
                );
            void try_remove_entity(Entity const&) override;
    };
};