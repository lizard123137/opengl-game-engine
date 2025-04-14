#pragma once

#include "consts.hpp"

#include <Graphics/shape_renderer.hpp>
#include <glm/glm.hpp>

#include <random>
#include <iostream>

class Ball {
    ShapeRenderer& renderer;

    glm::vec2 position;
    glm::vec2 velocity;
    glm::vec3 color;
public:
    Ball(ShapeRenderer& renderer);

    glm::vec2 getPosition();
    void draw();
    void update();
    void checkBouncePaddle(double paddle_pos, bool is_player);
};
