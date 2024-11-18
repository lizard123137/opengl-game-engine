#ifndef WINDOW_MANAGER_H
#define WINDOW_MANAGER_H

#include <Libs/glad.h>
#include <GLFW/glfw3.h>

class WindowManager {
public:
    static GLFWwindow* window;

    static GLFWwindow* InitWindow(const char *name, int width, int height); 
    static GLFWwindow* GetWindow();

private:
    WindowManager() { }
};

#endif