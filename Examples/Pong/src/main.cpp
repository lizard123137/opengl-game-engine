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

const unsigned int PADDLE_WIDTH = 20;
const unsigned int PADDLE_HEIGHT = 100;
const unsigned int PADDLE_OFFSET = 30;

const double COMPUTER_TARGET_SENSITIVITY = 5;

const double PADDLE_SPEED = 4;

const glm::vec3 BALL_COLOR = glm::vec3(1.0f, 1.0f, 1.0f);
const glm::vec3 PADDLE_COLOR = glm::vec3(1.0f, 1.0f, 1.0f);

static unsigned int player_h = static_cast<unsigned int>(SCREEN_HEIGHT / 2.0);
static unsigned int computer_h = static_cast<unsigned int>(SCREEN_HEIGHT / 2.0);

static unsigned int ball_speed = 4;
static glm::vec2 ball_pos = glm::vec2(SCREEN_WIDTH/2.0f, SCREEN_HEIGHT/2.0f);
static glm::vec2 ball_vel; // Set in main

static bool game_keys[GLFW_KEY_LAST];

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode);
void update_ball_velocity(double paddle_pos, bool is_player);

bool is_in_player_zone(glm::vec2 pos);
bool is_in_computer_zone(glm::vec2 pos);

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
    
    // TODO fix case where the ball angle is so steep that the game is unplayable
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
        if (player_h > PADDLE_HEIGHT / 2.0 && game_keys[GLFW_KEY_UP])
            player_h -= static_cast<unsigned int>(PADDLE_SPEED);
        if (player_h < SCREEN_HEIGHT - PADDLE_HEIGHT / 2.0 && game_keys[GLFW_KEY_DOWN])
            player_h += static_cast<unsigned int>(PADDLE_SPEED);

        // Update computer position
        if (computer_h > PADDLE_HEIGHT / 2.0 && computer_h > ball_pos.y)
            computer_h -= static_cast<unsigned int>(PADDLE_SPEED);
        else if (computer_h < SCREEN_HEIGHT - PADDLE_HEIGHT / 2.0 && computer_h < ball_pos.y)
            computer_h += static_cast<unsigned int>(PADDLE_SPEED);

        // Check for ball collisions
        if(is_in_player_zone(ball_pos)) {
            if(ball_pos.y < player_h && ball_pos.y > player_h - PADDLE_HEIGHT) {
                // TODO play bounce sound
                update_ball_velocity(player_h, true);
            }
        }
        // Enemy collision
        if(is_in_computer_zone(ball_pos)) {
            if(ball_pos.y < computer_h && ball_pos.y > computer_h - PADDLE_HEIGHT) {
                // TODO play bounce sound
                update_ball_velocity(computer_h, false);
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

bool is_in_player_zone(glm::vec2 pos) {
    return pos.x <= PADDLE_OFFSET && pos.x > PADDLE_OFFSET - PADDLE_WIDTH;
}

bool is_in_computer_zone(glm::vec2 pos) {
    return pos.x >= SCREEN_WIDTH - PADDLE_WIDTH - PADDLE_OFFSET && pos.x < SCREEN_WIDTH - PADDLE_OFFSET;
}

void update_ball_velocity(double paddle_pos, bool is_player) {
    /**
     * This part is super weird until you realize two things
     * Firstly: (0,0) is the top left of the screen
     * Secondly: The paddle position is actually its center
     * 
     * To explain how we calculate this we will need to use out **imagination**
     * Imagine that the paddle top is at height 0 (the top of the screen),
     * now we know that it's bottom is at PADDLE_HEIGHT.
     * 
     * We can calculate the remapped ball position by just adding the original paddle top
     */

    // TODO switch to having player be drawn from corner
    // Its way more intuitive that way. Preferably top left corner
    double ball_remapped = ball_pos.y - paddle_pos + PADDLE_HEIGHT;
    double paddle_range = ball_remapped / PADDLE_HEIGHT;
    double ball_angle = (M_PI * paddle_range) - M_PI / 2.0;
    
    // Update ball direction
    ball_vel = glm::vec2(std::cos(ball_angle), std::sin(ball_angle)) * static_cast<float>(ball_speed);

    // Flip direction for computer
    if (!is_player)
        ball_vel *= -1;
}