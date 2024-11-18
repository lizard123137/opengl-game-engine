#include <Utils/window_manager.hpp>

GLFWwindow* WindowManager::window;

GLFWwindow* WindowManager::InitWindow(const char *name, int width, int height) {
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    window = glfwCreateWindow(width, height, name, nullptr, nullptr);
    glfwMakeContextCurrent(window);

    return window;
}

GLFWwindow* WindowManager::GetWindow() {
    return window;
}