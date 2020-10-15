#include "gangine.h"

#include "input.h"

#include <GL/glut.h>
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
        color->r = color->b = 0;
        component::Transform* transform = static_cast<component::Transform*>(em.add_component(component::transform));
        component::Speed* speed = static_cast<component::Speed*>(em.add_component(component::speed));
        speed->dz = 1e-2;
    /*Entity& entity = */em.end_new(); // Entity has no purpose as of now

    debugRender->add_visible(transform, color);
    speedSystem->add_entity(speed, transform);

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

    GLuint vertexArrayId;
    glGenVertexArrays(1, &vertexArrayId);
    glBindVertexArray(vertexArrayId);

    return true;
}


void
GAngine::clean_up()
{
    // TODO
}

double
clock_to_milliseconds(clock_t t)
{
    return t/(double)CLOCKS_PER_SEC * 1000.0;
}

int
GAngine::game_loop()
{
    clock_t previous = clock();
    clock_t lag = 0;

    clock_t measureTimer = 0;
    unsigned int frames = 0;
    unsigned int updates = 0;
    double fps = 1.0;
    double ups = 1.0;

    running = true;
    while (running)
    {
        clock_t current = clock();
        clock_t elapsed = current - previous;

        previous = current;
        lag += elapsed;
        measureTimer += elapsed;

        handle_events(elapsed);

        while (lag > CLOCKS_PER_UPATE)
        {
            update();
            updates++;
            lag -= CLOCKS_PER_UPATE;
        }
        render(lag / CLOCKS_PER_UPATE);
        frames++;

        if (measureTimer > CLOCKS_PER_SEC)
        {
            fps = (double)frames * 0.5 + frames * 0.5;
            ups = (double)updates * 0.5 + updates * 0.5;

            frames = 0;
            updates = 0;

            std::cout << "New measure" << std::endl;
            std::cout << "FPS : " << fps << std::endl;
            std::cout << "UPS : " << ups << std::endl;
            std::cout << "Frame duration  : " << 1.0 / fps << std::endl;
            std::cout << "Update duration : " << 1.0 / ups << std::endl;

            measureTimer -= CLOCKS_PER_SEC;
        }
    }

    return 0;
}


void
GAngine::handle_events(int ticks)
{
    Input& input = Input::get_instance();
    input.update(window, ticks);

    if (
        input.get_key(GLFW_KEY_ESCAPE).is_down()
        ||
        glfwWindowShouldClose(window) != 0
    )
    {
        running = false;
    }
}


void
GAngine::update()
{
    speedSystem->update();
}

void
GAngine::render(double frame_advance)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    debugRender->update();

    glfwSwapBuffers(window);
    glfwPollEvents();
}
