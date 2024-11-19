#include <iostream>
#include <vector>
#include <filesystem>

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
#include <Graphics/sprite_renderer.hpp>
#include <Graphics/texture.hpp>

const unsigned int SCREEN_WIDTH = 800;
const unsigned int SCREEN_HEIGHT = 600;

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode);



int main(int argc, char **argv) {
    GLFWwindow *window = WindowManager::InitWindow("Pong", SCREEN_WIDTH, SCREEN_HEIGHT);
    glfwSetKeyCallback(window, key_callback);

    std::cout << std::filesystem::current_path() << std::endl;
    
    ResourceManager::LoadShader("../../../Examples/Pong/shaders/vert.glsl", "../../..Examples/Pong/shaders/frag.glsl", nullptr, "sprite");
    ResourceManager::LoadTexture("../../../Examples/Pong/resources/awesomeface.png", true, "test");

    glm::mat4 projection = glm::ortho(
        0.0f,
        static_cast<float>(SCREEN_WIDTH),
        static_cast<float>(SCREEN_HEIGHT),
        0.0f,
        -1.0f,
        1.0f
    );

    ResourceManager::GetShader("sprite").setInt("image", 0, true);
    ResourceManager::GetShader("sprite").setMat4("projection", projection);

    SpriteRenderer renderer(ResourceManager::GetShader("sprite"));

    while(!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        renderer.DrawSprite(
            ResourceManager::GetTexture("test"),
            glm::vec2(200.0f, 200.0f),
            glm::vec2(300.0f, 400.0f),
            45.0f,
            glm::vec3(0.0f, 1.0f, 0.0f)
        );

        glfwSwapBuffers(window);
    }

    ResourceManager::Clear();

    glfwTerminate();
    return 0;
}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}