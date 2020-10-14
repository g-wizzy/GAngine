#pragma once

#include "entity.h"

#include <glm/glm.hpp>

namespace component
{
    enum Type
    {
        transform,
        color,
        speed,
    };

    struct Component
    {
        Component(Entity& entity) : entity(entity) {}
        Entity& entity;
    };

    struct Transform : public Component
    {
        Transform(
            Entity& entity,
            glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3 size = glm::vec3(1.0f, 1.0f, 1.0f),
            glm::vec3 eulerAngles = glm::vec3(0.0f, 0.0f, 0.0f)
        ) :
            Component(entity),
            position(position),
            size(size),
            eulerAngles(eulerAngles)
            {}

        glm::vec3 position;
        glm::vec3 size;
        glm::vec3 eulerAngles;
    };

    struct Color : public Component
    {
        Color(
            Entity& entity,
            float r = 1.0f,
            float g = 1.0f,
            float b = 1.0f,
            float a = 1.0f
        ) :
            Component(entity),
            r(r),
            g(g),
            b(b),
            a(a)
            {}
            
        float r, g, b, a;
    };

    struct Speed : public Component
    {
        Speed(
            Entity& entity,
            float dx = 0,
            float dy = 0,
            float dz = 0
        ) :
            Component(entity),
            dx(dx),
            dy(dy),
            dz(dz)
            {}

        float dx, dy, dz;
    };
};