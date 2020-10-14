#include "systems/debugrender.h"

#include <GL/glew.h>
#include <GL/glu.h>
#include <glm/gtc/matrix_transform.hpp>

using namespace ga_system;

void
DebugRender::update()
{
    static const glm::mat4 projection = glm::perspective(
        glm::radians(60.0f),
        16.0f / 9.0f,
        0.1f,
        10.0f
    );

    for (auto it = entities.begin(); it != entities.end(); ++it)
    {
        component::Color* color = static_cast<component::Color*>((*it)[component::color]);
        component::Transform* transform = static_cast<component::Transform*>((*it)[component::transform]);

        // Debug means cube
        static const GLfloat g_vertex_buffer_data[] = {
            -1.0f,-1.0f,-1.0f, // triangle 1 : begin
            -1.0f,-1.0f, 1.0f,
            -1.0f, 1.0f, 1.0f, // triangle 1 : end
            1.0f, 1.0f,-1.0f, // triangle 2 : begin
            -1.0f,-1.0f,-1.0f,
            -1.0f, 1.0f,-1.0f, // triangle 2 : end
            1.0f,-1.0f, 1.0f,
            -1.0f,-1.0f,-1.0f,
            1.0f,-1.0f,-1.0f,
            1.0f, 1.0f,-1.0f,
            1.0f,-1.0f,-1.0f,
            -1.0f,-1.0f,-1.0f,
            -1.0f,-1.0f,-1.0f,
            -1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f,-1.0f,
            1.0f,-1.0f, 1.0f,
            -1.0f,-1.0f, 1.0f,
            -1.0f,-1.0f,-1.0f,
            -1.0f, 1.0f, 1.0f,
            -1.0f,-1.0f, 1.0f,
            1.0f,-1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f,-1.0f,-1.0f,
            1.0f, 1.0f,-1.0f,
            1.0f,-1.0f,-1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f,-1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f, 1.0f,-1.0f,
            -1.0f, 1.0f,-1.0f,
            1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f,-1.0f,
            -1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f, 1.0f,
            1.0f,-1.0f, 1.0f
            };

        glm::mat4 view = glm::lookAt(
            camera->position,
            transform->position,
            glm::vec3(0.0f, 0.0f, 1.0f)
        );

        glm::mat4 model = glm::scale(glm::mat4(1.0f), transform->size);
        model = glm::rotate(model, transform->eulerAngles.x, glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::rotate(model, transform->eulerAngles.y, glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::rotate(model, transform->eulerAngles.z, glm::vec3(0.0f, 0.0f, 1.0f));
        model = glm::translate(model, transform->position);

        //GLuint matrixId = glGetUniformLocation()
    }
}

void
DebugRender::add_visible(
    component::Transform* transform,
    component::Color* color
)
{
    std::map<component::Type, component::Component*> map;
    map[component::color] = color;
    map[component::transform] = transform;

    entities.push_back(map);
}

void
DebugRender::set_camera(
    component::Transform* transform
)
{
    camera = transform;
}

void
DebugRender::try_remove_entity(Entity const& entity)
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