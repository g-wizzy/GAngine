#pragma once

#include "entity.h"

namespace component
{
    enum Type
    {
        size,
        position,
        color,
        speed
    };

    struct Component
    {
        Component(Entity& entity) : entity(entity) {}
        Entity& entity;
    };

    struct Size : public Component
    {
        Size(Entity& entity, int w = 0, int h = 0) :
            Component(entity),
            w(w),
            h(h)
            {}
        int w, h;
    };

    struct Position : public Component
    {
        Position(Entity& entity, int x = 0, int y = 0) :
            Component(entity),
            x(x),
            y(y)
            {}
        int x, y;
    };

    struct Color : public Component
    {
        Color(Entity& entity, int r = 0xFF, int g = 0xFF, int b = 0xFF, int a = 0xFF) :
            Component(entity),
            r(r),
            g(g),
            b(b),
            a(a)
            {}
        int r, g, b, a;
    };

    struct Speed : public Component
    {
        Speed(Entity& entity, int dx = 0, int dy = 0) :
            Component(entity),
            dx(dx),
            dy(dy)
            {}
        int dx, dy;
    };
};