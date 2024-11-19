#ifndef WINDOW_MANAGER_H
#define WINDOW_MANAGER_H

#include <Libs/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

class WindowManager {
public:
    static GLFWwindow* window;

    static GLFWwindow* InitWindow(const char *name, int width, int height); 
    static GLFWwindow* GetWindow();

private:
    WindowManager() { }

    static void framebuffer_size_callback(GLFWwindow *window, int width, int height);
    static void GLAPIENTRY debug_callback(GLenum source, 
                            GLenum type, 
                            unsigned int id, 
                            GLenum severity, 
                            GLsizei length, 
                            const char *message, 
                            const void *userParam);
};

#endif