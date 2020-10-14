#include "gangine.h"

#include "input.h"

#include <GL/glu.h>
#include <iostream>


GAngine::GAngine() :
    running(true)
    {}

GAngine::~GAngine()
{

}


int
GAngine::run()
{
    if (!init())
    {
        return -1;
    }

    speedSystem = new ga_system::Speed();
    debugRender = new ga_system::DebugRender();
    create_entities();

    int errcode = game_loop();

    clean_up();

    return errcode;
}

/**
 * This method makes no sense in many ways. Here are the major issues at play:
 * - This should be the work of several factories, reading from level files
 * - components of the same type should be instanciated at the same time for optimization
 * But for testing purposes, this shall do.
 */
void
GAngine::create_entities()
{
    EntityManager& em = EntityManager::get_instance();

    // Cube
    em.begin_new();
        component::Color* color = static_cast<component::Color*>(em.add_component(component::color)); // defaults to white
        component::Transform* transform = static_cast<component::Transform*>(em.add_component(component::transform));
        // component::Speed* speed = static_cast<component::Speed*>(em.add_component(component::speed));
        // speed->dx = 5;
        // speed->dy = 5;
    /*Entity& entity = */em.end_new(); // Entity has no purpose as of now

    debugRender->add_visible(transform, color);
    //speedSystem->add_entity(speed, pos);

    // Camera
    em.begin_new();
        component::Transform* cameraTransform = static_cast<component::Transform*>(em.add_component(component::transform));
        cameraTransform->position = glm::vec3(5, 3, 2);
    em.end_new();

    debugRender->set_camera(cameraTransform);
}


bool
GAngine::init()
{
    glewExperimental = true;
    if (!glfwInit())
    {
        std::cout << "GLFW init failed" << std::endl;
        return false;
    }

    glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenG

    window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "GAngine", NULL, NULL);
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        return false;
    }

    glfwMakeContextCurrent(window);
    glewExperimental = true;
    if (glewInit() != GLEW_OK)
    {
        std::cout << "GLEW init failed" << std::endl;
        return false;
    }

    return true;
}


void
GAngine::clean_up()
{
    // TODO
}

int
GAngine::game_loop()
{
    double previous = 1000 * glfwGetTime();
    double lag = 0.0;

    running = true;
    while (running)
    {
        double current = 1000 * glfwGetTime();
        double elapsed = current - previous;
        previous = current;
        lag += elapsed;

        handle_events();
        while (lag > MS_PER_UPATE)
        {
            update();
            lag -= MS_PER_UPATE;
        }
        render(lag / MS_PER_UPATE);
    }

    return 0;
}


void
GAngine::handle_events()
{
    running = !(
        glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS
        ||
        glfwWindowShouldClose(window) != 0
    );
}


void
GAngine::update()
{
    speedSystem->update();
}

void
GAngine::render(double frame_advance)
{
    glClear(GL_COLOR_BUFFER_BIT);

    debugRender->update();

    glfwSwapBuffers(window);
    glfwPollEvents();
}