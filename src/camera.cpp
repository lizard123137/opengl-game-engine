#include "camera.hpp"

Camera::Camera(int width, int height, glm::vec3 position) {
    this->width = width;
    this->height = height;
    this->Position = position;
}

void Camera::Matrix(float FOVdeg, float nearPlane, float farPlane, Shader &shader, const char *uniform) {
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);

    view = glm::lookAt(this->Position, this->Position + this->Direction, this->Up);
    projection = glm::perspective(glm::radians(FOVdeg), (float)(this->width / this->height), nearPlane, farPlane);

    glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(projection * view));
}

void Camera::Inputs(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        this->Position += this->speed * this->Direction;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        this->Position -= this->speed * this->Direction;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        this->Position -= glm::normalize(glm::cross(this->Direction, this->Up)) * this->speed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        this->Position += glm::normalize(glm::cross(this->Direction, this->Up)) * this->speed;
}