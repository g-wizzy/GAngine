#include "systems/speed.h"

using namespace ga_system;

void Speed::update()
{
    for (auto it = entities.begin(); it != entities.end(); ++it)
    {
        component::Speed* speed = static_cast<component::Speed*>((*it)[component::speed]);
        component::Transform* transform = static_cast<component::Transform*>((*it)[component::transform]);

        transform->position.x += speed->dx;
        transform->position.y += speed->dy;
    }
}

void Speed::add_entity(component::Speed* speed, component::Transform* transform)
{
    std::map<component::Type, component::Component*> map;
    map[component::speed] = speed;
    map[component::transform] = transform;

    entities.push_back(map);
}

void Speed::try_remove_entity(const Entity& entity)
{
    for (auto it = entities.begin(); it != entities.end();)
    {
        if ((*it)[component::speed]->entity == entity)
        {
            it = entities.erase(it);
        }
        else
        {
            ++it;
        }
    }
}