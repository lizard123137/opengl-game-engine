#include <iostream>
#include <vector>
#include <filesystem>
#include <random>

#include <Libs/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <Utils/resource_manager.hpp>
#include <Utils/window_manager.hpp>

#include <Graphics/camera.hpp>
#include <Graphics/mesh.hpp>
#include <Graphics/shader.hpp>
#include <Graphics/shape_renderer.hpp>
#include <Graphics/sprite_renderer.hpp>
#include <Graphics/texture.hpp>

const unsigned int SCREEN_WIDTH = 800;
const unsigned int SCREEN_HEIGHT = 600;

const unsigned int BALL_SIZE = 10;

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode);

int main(int argc, char **argv) {
    GLFWwindow *window = WindowManager::InitWindow("Pong", SCREEN_WIDTH, SCREEN_HEIGHT);
    glfwSetKeyCallback(window, key_callback);

    std::cout << std::filesystem::current_path() << std::endl;
    
    ResourceManager::LoadShader("../../../Examples/Pong/shaders/vert.glsl", "../../../Examples/Pong/shaders/frag.glsl", nullptr, "sprite");

    glm::mat4 projection = glm::ortho(
        0.0f,
        static_cast<float>(SCREEN_WIDTH),
        static_cast<float>(SCREEN_HEIGHT),
        0.0f,
        -1.0f,
        1.0f
    );

    ShapeRenderer renderer(ResourceManager::GetShader("sprite"));

    ResourceManager::GetShader("sprite").setInt("image", 0, true);
    ResourceManager::GetShader("sprite").setMat4("projection", projection, true);

    while(!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        renderer.DrawCircle(
            glm::vec2(50.0, 50.0f),
            glm::vec2(10.0, 10.0),
            5.0f
        );

        glfwSwapBuffers(window);
    }

    ResourceManager::Clear();

    glfwTerminate();
    return 0;
}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

}