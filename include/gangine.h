#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "input.h"
#include "systems.h"
#include "entitymanager.h"

#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 1000

class GAngine
{
private:
    const short MS_PER_UPATE = 16;

    GLFWwindow* window = nullptr;

    bool init();
    void clean_up();
    bool running;

    int game_loop();
    void handle_events();
    void update();
    void render(double frame_advance);

    ga_system::Speed* speedSystem;
    ga_system::DebugRender* debugRender;

    void create_entities();

public:
    GAngine();
    ~GAngine();

    int run();
};