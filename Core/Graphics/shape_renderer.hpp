#ifndef SHAPE_RENDERER_H
#define SHAPE_RENDERER_H

#include <Libs/glad.h>

#include <Graphics/shader.hpp>
#include <Graphics/texture.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class ShapeRenderer {
public:
    ShapeRenderer(Shader &shader);

    void DrawRect(
        glm::vec2 position,
        glm::vec2 size = glm::vec2(10.0f, 10.0f),
        float rotate = 0.0f,
        glm::vec3 color = glm::vec3(1.0f));
    
private:
    Shader shader;
};

#endif