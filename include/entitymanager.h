#pragma once

#include "entity.h"
#include "components.h"

class EntityManager
{
    private:
        EntityManager() :
            current(-1)
            {}

        Entity current;

    public:
        static EntityManager& get_instance();

        EntityManager(EntityManager const&) = delete;
        void operator=(EntityManager const&) = delete;


        void begin_new();
        component::Component* add_component(component::Type const&);
        Entity& end_new();
};