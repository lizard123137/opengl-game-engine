#include "paddle.hpp"
#include "inputs.hpp"

glm::vec2 Paddle::calculatePlayerPos() {
    return glm::vec2(PADDLE_OFFSET - PADDLE_WIDTH/2.0f, this->position - PADDLE_HEIGHT/2.0f);
}

glm::vec2 Paddle::calculateOpponentPos() {
    return glm::vec2(SCREEN_WIDTH - PADDLE_OFFSET - PADDLE_WIDTH/2.0f, this->position - PADDLE_HEIGHT/2.0f);
}

void Paddle::moveUp(float ball_height) {
    if (this->is_player) {
        if (this->position > PADDLE_HEIGHT / 2.0 && game_keys[GLFW_KEY_UP])
            this->position -= static_cast<unsigned int>(PADDLE_SPEED);
    } else {
        if (this->position > PADDLE_HEIGHT / 2.0 && this->position > ball_height)
            this->position -= static_cast<unsigned int>(PADDLE_SPEED);
    }
}

void Paddle::moveDown(float ball_height) {
    if (this->is_player) {
        if (this->position < SCREEN_HEIGHT - PADDLE_HEIGHT / 2.0 && game_keys[GLFW_KEY_DOWN])
            this->position += static_cast<unsigned int>(PADDLE_SPEED);
    } else {
        if (this->position < SCREEN_HEIGHT - PADDLE_HEIGHT / 2.0 && this->position < ball_height)
            this->position += static_cast<unsigned int>(PADDLE_SPEED);
    }
}

double Paddle::getPosition() {
    return this->position;
}

void Paddle::draw() {
    if (this->is_player) {
        renderer.DrawRect(
            this->calculatePlayerPos(),
            this->size,
            0.0f,
            this->color
        );
    } else {
        renderer.DrawRect(
            this->calculateOpponentPos(),
            this->size,
            0.0f,
            this->color
        );
    }
}

void Paddle::update(float ball_height) {
    this->moveUp(ball_height);
    this->moveDown(ball_height);
}
