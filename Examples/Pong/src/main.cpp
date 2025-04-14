#include "ball.hpp"
#include "consts.hpp"
#include "inputs.hpp"
#include "paddle.hpp"

#include <iostream>
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

int main(int argc, char **argv) {
    GLFWwindow *window = WindowManager::InitWindow("Pong", SCREEN_WIDTH, SCREEN_HEIGHT);
    glfwSetKeyCallback(window, input_callback);

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

    Ball ball(renderer);
    Paddle paddle_player(renderer, glm::vec2(PADDLE_WIDTH, PADDLE_HEIGHT), PADDLE_COLOR, true);
    Paddle paddle_opponent(renderer, glm::vec2(PADDLE_WIDTH, PADDLE_HEIGHT), PADDLE_COLOR, false);

    while(!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // TODO switch over to delta time to account for framerate variation
        ball.update();
        // TODO fix paddle bounces
        ball.checkBouncePaddle(paddle_player.getPosition(), true);
        ball.checkBouncePaddle(paddle_opponent.getPosition(), false);

        paddle_player.update(ball.getPosition().y);
        paddle_opponent.update(ball.getPosition().y);

        ball.draw();
        paddle_player.draw();
        paddle_opponent.draw();

        glfwSwapBuffers(window);
    }

    ResourceManager::Clear();

    glfwTerminate();
    return 0;
}
