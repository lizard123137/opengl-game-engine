#include <Graphics/shape_renderer.hpp>

ShapeRenderer::ShapeRenderer(Shader& shader) {
    this->shader = shader;
}

void ShapeRenderer::DrawVertices(
    std::vector<float> vertices,
    glm::vec2 position,
    glm::vec2 size,
    float rotate,
    glm::vec3 color
) {
    unsigned int VAO, VBO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(position, 0.0f));

    model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
    model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));

    model = glm::scale(model, glm::vec3(size, 1.0f));

    this->shader.setMat4("model", model, true);
    this->shader.setVec3f("color", color);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLE_FAN, 0, vertices.size());
    glBindVertexArray(0);

    glDeleteVertexArrays(1, &VAO);
}

void ShapeRenderer::DrawRect(
    glm::vec2 position,
    glm::vec2 size,
    float rotate,
    glm::vec3 color
) {
    std::vector<float> vertices = {
        0.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, 0.0f,
    };

    this->DrawVertices(vertices, position, size, rotate, color);
}
    
void ShapeRenderer::DrawCircle(
    glm::vec2 position,
    glm::vec2 size,
    float r,
    glm::vec3 color
) {
    std::vector<float> vertices = {};

    for (int i = 0; i <= CIRCLE_DETAIL; i++) {
        float angle = 2.0f * M_PI * (float)(i) / (float)(CIRCLE_DETAIL);
        float x, y;
        if (angle != 0.0f) {
            x = r * cos(angle);
            y = r * sin(angle);
        } else {
            x = r;
        }
        vertices.push_back(x);
        vertices.push_back(y);
    }

    this->DrawVertices(vertices, position, size, 0.0, color);
}