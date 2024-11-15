#include <iostream>
#include <GLFW/glfw3.h>

int main(int argc, char **argv) {
    GLFWwindow *window;

    if (!glfwInit()) {
        std::cout << "Couldn't initialize glfw!" << std::endl;
        return -1;
    }

    window = glfwCreateWindow(800, 600, "opengl-game-engine", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    while(!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}