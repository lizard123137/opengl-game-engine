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
#include <Graphics/shape_renderer.hpp>
#include <Graphics/sprite_renderer.hpp>
#include <Graphics/texture.hpp>

const unsigned int SCREEN_WIDTH = 800;
const unsigned int SCREEN_HEIGHT = 600;

const unsigned int BALL_SIZE = 20;

const unsigned int PADDLE_WIDTH = 20;
const unsigned int PADDLE_HEIGHT = 100;
const unsigned int PADDLE_OFFSET = 30;

const glm::vec3 BALL_COLOR = glm::vec3(1.0f, 1.0f, 1.0f);
const glm::vec3 PADDLE_COLOR = glm::vec3(1.0f, 1.0f, 1.0f);

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode);

int main(int argc, char **argv) {
    GLFWwindow *window = WindowManager::InitWindow("Pong", SCREEN_WIDTH, SCREEN_HEIGHT);
    glfwSetKeyCallback(window, key_callback);

    std::cout << std::filesystem::current_path() << std::endl;
    
    ResourceManager::LoadShader("../../../Examples/Pong/shaders/vert.glsl", "../../../Examples/Pong/shaders/frag.glsl", nullptr, "sprite");
    ResourceManager::LoadTexture("../../../Examples/Pong/resources/awesomeface.png", true, "test");

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

        renderer.DrawRect(
            glm::vec2(PADDLE_OFFSET - PADDLE_WIDTH/2.0f, SCREEN_HEIGHT/2.0f - PADDLE_HEIGHT/2.0f),
            glm::vec2(PADDLE_WIDTH, PADDLE_HEIGHT),
            0.0f,
            PADDLE_COLOR
        );

        renderer.DrawRect(
            glm::vec2(SCREEN_WIDTH - PADDLE_OFFSET - PADDLE_WIDTH/2.0f, SCREEN_HEIGHT/2.0f - PADDLE_HEIGHT/2.0f),
            glm::vec2(PADDLE_WIDTH, PADDLE_HEIGHT),
            0.0f,
            PADDLE_COLOR
        );

        renderer.DrawRect(
            glm::vec2(SCREEN_WIDTH / 2.0f - BALL_SIZE / 2.0f, SCREEN_HEIGHT / 2.0f - BALL_SIZE / 2.0f),
            glm::vec2(BALL_SIZE, BALL_SIZE),
            0.0f,
            BALL_COLOR
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