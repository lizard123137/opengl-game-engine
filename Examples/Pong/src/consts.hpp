#pragma once

#include <glm/glm.hpp>

const unsigned int SCREEN_WIDTH = 800;
const unsigned int SCREEN_HEIGHT = 600;

const unsigned int BALL_SIZE = 10;
const float BALL_SPEED = 4;

const unsigned int PADDLE_WIDTH = 20;
const unsigned int PADDLE_HEIGHT = 100;
const unsigned int PADDLE_OFFSET = 30;
const double PADDLE_SPEED = 4;

const glm::vec3 BALL_COLOR = glm::vec3(1.0f, 1.0f, 1.0f);
const glm::vec3 PADDLE_COLOR = glm::vec3(1.0f, 1.0f, 1.0f);

const double COMPUTER_TARGET_SENSITIVITY = 5;
