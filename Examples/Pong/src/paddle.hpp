#pragma once

#include "consts.hpp"

#include <Graphics/shape_renderer.hpp>
#include <glm/glm.hpp>

class Paddle {
    ShapeRenderer& renderer;

    double position;
    glm::vec2 size;
    glm::vec3 color;

    bool is_player;

    glm::vec2 calculatePlayerPos();
    glm::vec2 calculateOpponentPos();
    void moveUp(float ball_height);
    void moveDown(float ball_height);
public:
    Paddle(
        ShapeRenderer& renderer,
        glm::vec2 size,
        glm::vec3 color,
        bool is_player
    ): renderer(renderer), size(size), color(color), is_player(is_player) { }

    double getPosition();
    void draw();
    void update(float ball_height);
};
