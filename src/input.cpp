#include "input.h"

#include <iostream>
#include <GLFW/glfw3.h>

Input::Input()
{
    init_key(GLFW_KEY_ESCAPE);
    init_key(GLFW_KEY_SPACE);
    init_key(GLFW_KEY_A);
    init_key(GLFW_KEY_S);
    init_key(GLFW_KEY_D);
}

Input&
Input::get_instance()
{
    static Input instance;

    return instance;
}

void
Input::update(
    GLFWwindow* window,
    int ticks
)
{
    for (auto it = keys.begin(); it != keys.end(); ++it)
    {
        update_key(window, ticks, it->first);
    }
}

void
Input::init_key(
    int key
)
{
    keys[key] = key_state_t();
}

void
Input::update_key(
    GLFWwindow* window,
    int ticks,
    int key
)
{
    if (glfwGetKey(window, key) == GLFW_PRESS)
    {
        keys[key].hold(ticks);
    }
    else
    {
        keys[key].release();
    }
    
}

const key_state_t&
Input::get_key(int key) const
{
    const static key_state_t inexistent_key;
    
    auto search = keys.find(key);
    if (search != keys.end())
    {
        return search->second;
    }
    else
    {
        std::cout << "WARNING : inexistent key lookup : " << glfwGetKeyName(key, 0) << std::endl;
        return inexistent_key;
    }
    
}