#pragma once

#include <GLFW/glfw3.h>

extern bool game_keys[GLFW_KEY_LAST];

void input_callback(GLFWwindow *window, int key, int scancode, int action, int mode);
