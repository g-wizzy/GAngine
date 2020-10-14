#pragma once

#include "systems/system.h"
#include "components.h"

#include <GL/glew.h>
#include <GL/gl.h>

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

            GLuint vertexBuffer;
            static const GLfloat g_vertex_buffer_data[];

        public:
            DebugRender();

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
