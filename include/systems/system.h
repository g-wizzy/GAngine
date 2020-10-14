#pragma once

#include "entity.h"

#include <GL/glew.h>
#include <GL/gl.h>

#include <vector>

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
            RenderSystem() {}
            virtual ~RenderSystem() {}
        
            virtual void update() override
            {
                glUseProgram(programId);
            }

        protected:
            GLuint programId;
    };
};
