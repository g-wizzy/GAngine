#include "systems/debugrender.h"

using namespace ga_system;


void DebugRender::update()
{
    for (auto it = entities.begin(); it != entities.end(); ++it)
    {
        component::Color* color = static_cast<component::Color*>((*it)[component::color]);
        component::Size* size = static_cast<component::Size*>((*it)[component::size]);
        component::Position* position = static_cast<component::Position*>((*it)[component::position]);

        SDL_SetRenderDrawColor(
            renderer,
            color->r,
            color->g,
            color->b,
            color->a
        );
        
        SDL_Rect rect;
        rect.x = position->x;
        rect.y = position->y;
        rect.w = size->w;
        rect.h = size->h;

        SDL_RenderFillRect(
            renderer,
            &rect
        );
    }
}

void DebugRender::add_entity(
    component::Color* color,
    component::Size* size,
    component::Position* position
)
{
    std::map<component::Type, component::Component*> map;
    map[component::color] = color;
    map[component::size] = size;
    map[component::position] = position;

    entities.push_back(map);
}

void DebugRender::try_remove_entity(Entity const& entity)
{
    for (auto it = entities.begin(); it != entities.end();)
    {
        if ((*it)[component::color]->entity == entity)
        {
            it = entities.erase(it);
        }
        else
        {
            ++it;
        }
        
    }
}