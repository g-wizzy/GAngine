#pragma once

#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>

#include "input.h"
#include "systems.h"
#include "entitymanager.h"

#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 1000

#define MS_PER_UPDATE 16

class GAngine
{
private:
    const short CLOCKS_PER_UPATE = CLOCKS_PER_SEC / 1000 * MS_PER_UPDATE;

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

    // debug
    void create_entities();

public:
    GAngine();
    ~GAngine();

    int run();
};