#pragma once

#include <map>

class GLFWwindow;

struct key_state_t
{
    unsigned int ticks_held = 0;

    bool is_down() const
    {
        return ticks_held > 0;
    }

    void hold(int ticks)
    {
        ticks_held += ticks;
    }

    void release()
    {
        ticks_held = 0;
    }
};

class Input
{
private:
    Input();

    void update_key(GLFWwindow* window, int ticks, int key);

    std::map<int, key_state_t> keys;

public:
    static Input& get_instance();
    Input(Input const&) = delete;
    void operator=(Input const&) = delete;

    void update(GLFWwindow* window, int ticks);
    const key_state_t& get_key(int key) const;
};