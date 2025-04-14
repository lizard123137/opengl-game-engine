#include "inputs.hpp"

bool game_keys[GLFW_KEY_LAST];

void input_callback(GLFWwindow *window, int key, int scancode, int action, int mode) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    else if (key == GLFW_KEY_UP && action == GLFW_PRESS) {
        game_keys[GLFW_KEY_UP] = true;
    }
    else if (key == GLFW_KEY_UP && action == GLFW_RELEASE) {
        game_keys[GLFW_KEY_UP] = false;
    }
    else if (key == GLFW_KEY_DOWN && action == GLFW_PRESS) {
        game_keys[GLFW_KEY_DOWN] = true;
    }
    else if (key == GLFW_KEY_DOWN && action == GLFW_RELEASE) {
        game_keys[GLFW_KEY_DOWN] = false;
    }
}
