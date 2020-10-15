#include "systems/debugrender.h"

#include "shaders.hpp"
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

using namespace ga_system;

const GLfloat DebugRender::g_vertex_buffer_data[] = {
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

const GLfloat DebugRender::g_uv_buffer_data[] = {
    0.000059f, 0.000004f,
    0.000103f, 0.336048f,
    0.335973f, 0.335903f,
    1.000023f, 0.000013f,
    0.667979f, 0.335851f,
    0.999958f, 0.336064f,
    0.667979f, 0.335851f,
    0.336024f, 0.671877f,
    0.667969f, 0.671889f,
    1.000023f, 0.000013f,
    0.668104f, 0.000013f,
    0.667979f, 0.335851f,
    0.000059f, 0.000004f,
    0.335973f, 0.335903f,
    0.336098f, 0.000071f,
    0.667979f, 0.335851f,
    0.335973f, 0.335903f,
    0.336024f, 0.671877f,
    1.000004f, 0.671847f,
    0.999958f, 0.336064f,
    0.667979f, 0.335851f,
    0.668104f, 0.000013f,
    0.335973f, 0.335903f,
    0.667979f, 0.335851f,
    0.335973f, 0.335903f,
    0.668104f, 0.000013f,
    0.336098f, 0.000071f,
    0.000103f, 0.336048f,
    0.000004f, 0.671870f,
    0.336024f, 0.671877f,
    0.000103f, 0.336048f,
    0.336024f, 0.671877f,
    0.335973f, 0.335903f,
    0.667969f, 0.671889f,
    1.000004f, 0.671847f,
    0.667979f, 0.335851f
};

DebugRender::DebugRender() :
    RenderSystem()
{
        glGenBuffers(1, &vertexBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

        glGenBuffers(1, &uvBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(g_uv_buffer_data), g_uv_buffer_data, GL_STATIC_DRAW);

        programId = load_shaders(
            "basic_vertex",
            "basic_fragment"
        );

        texture = load_DDS("uvtemplate");
        textureId = glGetUniformLocation(programId, "texSampler");
}


void
DebugRender::update()
{
    RenderSystem::update();

    static const glm::mat4 projection = glm::perspective(
        glm::radians(60.0f),
        16.0f / 9.0f,
        0.1f,
        10.0f
    );

    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    for (auto it = entities.begin(); it != entities.end(); ++it)
    {
        component::Color* color = static_cast<component::Color*>((*it)[component::color]);
        component::Transform* transform = static_cast<component::Transform*>((*it)[component::transform]);

        // Create matrices
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

        glm::mat4 mvp = projection * view * model;

        // Give them to GLSL
        GLuint matrixId = glGetUniformLocation(programId, "mvp");
        glUniformMatrix4fv(matrixId, 1, GL_FALSE, &mvp[0][0]);

        // Load texture
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        glUniform1i(textureId, 0);

        // Load vertices
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
        glVertexAttribPointer(
            0,
            3,
            GL_FLOAT,
            GL_FALSE,
            0,
            (void*)0
        );

        // Load UV
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
        glVertexAttribPointer(
            1,
            2,
            GL_FLOAT,
            GL_FALSE,
            0,
            (void*)0
        );

        glDrawArrays(GL_TRIANGLES, 0, 36);

        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
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
DebugRender::try_remove_entity(
    Entity const& entity
)
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