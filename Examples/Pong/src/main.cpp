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

const unsigned int BALL_SIZE = 20;

const unsigned int PADDLE_WIDTH = 20;
const unsigned int PADDLE_HEIGHT = 100;
const unsigned int PADDLE_OFFSET = 30;

const double PADDLE_SPEED = 4;

const glm::vec3 BALL_COLOR = glm::vec3(1.0f, 1.0f, 1.0f);
const glm::vec3 PADDLE_COLOR = glm::vec3(1.0f, 1.0f, 1.0f);

static unsigned int player_h = static_cast<unsigned int>(SCREEN_HEIGHT / 2.0);
static unsigned int computer_h = static_cast<unsigned int>(SCREEN_HEIGHT / 2.0);

static unsigned int ball_speed = 2;
static glm::vec2 ball_pos = glm::vec2(SCREEN_WIDTH/2.0f, SCREEN_HEIGHT/2.0f);
static glm::vec2 ball_vel; // Set in main

static bool game_keys[GLFW_KEY_LAST];

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

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist(0.0f, 2.0f * M_PI);
    
    float ball_angle = dist(gen);
    ball_vel = glm::vec2(std::cos(ball_angle), std::sin(ball_angle)) * static_cast<float>(ball_speed);

    while(!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        // TODO switch over to delta time to account for framerate variation
        ball_pos += ball_vel;

        if (ball_pos.y <= 0 || ball_pos.y >= SCREEN_HEIGHT)
            ball_vel.y *= -1;

        if (ball_pos.x <= 0) {
            ball_pos = glm::vec2(SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
            std::cout << "Computer wins" << std::endl;
        }

        if (ball_pos.x >= SCREEN_WIDTH) {
            ball_pos = glm::vec2(SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
            std::cout << "Player wins" << std::endl;
        }

        // Update player position
        if (game_keys[GLFW_KEY_UP])
            player_h -= static_cast<unsigned int>(PADDLE_SPEED);
        if (game_keys[GLFW_KEY_DOWN])
            player_h += static_cast<unsigned int>(PADDLE_SPEED);

        // Update computer position
        // TODO fix integer overflow
        if (computer_h > ball_pos.y)
            computer_h -= static_cast<unsigned int>(PADDLE_SPEED);
        else if (computer_h < ball_pos.y)
            computer_h += static_cast<unsigned int>(PADDLE_SPEED);

        // Check for collisions
        // Player collision
        if(ball_pos.x <= PADDLE_WIDTH + PADDLE_OFFSET && ball_pos.x > PADDLE_OFFSET) {
            if(ball_pos.y < player_h + PADDLE_HEIGHT && ball_pos.y > player_h) {
                // TODO play bounce sound
                // TODO add bound angle based on ball pos
                ball_vel *= -1;
            }
        }
        // Enemy collision
        if(ball_pos.x >= SCREEN_WIDTH - PADDLE_WIDTH - PADDLE_OFFSET && ball_pos.x < SCREEN_WIDTH - PADDLE_OFFSET) {
            if(ball_pos.y < computer_h + PADDLE_HEIGHT && ball_pos.y > computer_h) {
                // TODO play bounce sound
                // TODO add bound angle based on ball pos
                ball_vel *= -1;
            }
        }


        // Player paddle
        renderer.DrawRect(
            glm::vec2(PADDLE_OFFSET - PADDLE_WIDTH/2.0f, player_h - PADDLE_HEIGHT/2.0f),
            glm::vec2(PADDLE_WIDTH, PADDLE_HEIGHT),
            0.0f,
            PADDLE_COLOR
        );

        // Computer paddle
        renderer.DrawRect(
            glm::vec2(SCREEN_WIDTH - PADDLE_OFFSET - PADDLE_WIDTH/2.0f, computer_h - PADDLE_HEIGHT/2.0f),
            glm::vec2(PADDLE_WIDTH, PADDLE_HEIGHT),
            0.0f,
            PADDLE_COLOR
        );

        renderer.DrawRect(
            glm::vec2(ball_pos.x, ball_pos.y),
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