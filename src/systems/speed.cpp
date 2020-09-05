#include "systems/speed.h"

using namespace ga_system;

void Speed::update()
{
    for (auto it = entities.begin(); it != entities.end(); ++it)
    {
        component::Speed* speed = static_cast<component::Speed*>((*it)[component::speed]);
        component::Position* position = static_cast<component::Position*>((*it)[component::position]);

        position->x += speed->dx;
        position->y += speed->dy;

        if (position->x < 0)
        {
            position->x = 0;
            speed->dx *= -1;
        }
        else if (position->x + 50 > 640)
        {
            position->x = 640 - 50;
            speed->dx *= -1;
        }

        if (position->y < 0)
        {
            position->y = 0;
            speed->dy *= -1;
        }
        else if (position->y + 50 > 480)
        {
            position->y = 480 -50;
            speed->dy *= -1;
        }
    }
}

void Speed::add_entity(component::Speed* speed, component::Position* position)
{
    std::map<component::Type, component::Component*> map;
    map[component::speed] = speed;
    map[component::position] = position;

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