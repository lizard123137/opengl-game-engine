#ifndef SHAPE_RENDERER_H
#define SHAPE_RENDERER_H

#include <cmath>
#include <vector>

#include <Libs/glad.h>

#include <Graphics/shader.hpp>
#include <Graphics/texture.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define CIRCLE_DETAIL 300

class ShapeRenderer {
public:
    ShapeRenderer(Shader &shader);

    void DrawVertices(
        std::vector<float> vertices,
        glm::vec2 position,
        glm::vec2 size,
        float rotate,
        glm::vec3 color
    );

    void DrawRect(
        glm::vec2 position,
        glm::vec2 size = glm::vec2(10.0f, 10.0f),
        float rotate = 0.0f,
        glm::vec3 color = glm::vec3(1.0f)
    );

    void DrawCircle(
        glm::vec2 position,
        glm::vec2 size = glm::vec2(10.0f, 10.0f),
        float r = 5.0f,
        glm::vec3 color = glm::vec3(1.0f)
    );
    
private:
    Shader shader;
};

#endif