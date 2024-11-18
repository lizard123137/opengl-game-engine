#include <iostream>
#include <vector>
#include <filesystem>

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
#include <Graphics/texture.hpp>

#define FOV             (45.0f)
#define SCREEN_WIDTH    (800)
#define SCREEN_HEIGHT   (600)

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode);

int main(int argc, char **argv) {
    GLFWwindow *window = WindowManager::InitWindow("Pong", SCREEN_WIDTH, SCREEN_HEIGHT);
    
    glfwSetKeyCallback(window, key_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glEnable(GL_DEPTH_TEST);

    std::cout << std::filesystem::current_path() << std::endl;
    Shader shader = ResourceManager::LoadShader("../../../Examples/Pong/shaders/vert.glsl", "../../..Examples/Pong/shaders/frag.glsl", nullptr, "main");
    Texture texture = ResourceManager::LoadTexture("../../../Examples/Pong/resources/test.jpg", false, "main");


    std::vector<Vertex> vertices = {
        Vertex { .Position = glm::vec3(0.5f, 0.5f, 0.0f), .TexCoords = glm::vec2(1.0f, 1.0f) },
        Vertex { .Position = glm::vec3(0.5f, -0.5f, 0.0f), .TexCoords = glm::vec2(1.0f, 0.0f) },
        Vertex { .Position = glm::vec3(-0.5f, -0.5f, 0.0f), .TexCoords = glm::vec2(0.0f, 0.0f)},
        Vertex { .Position = glm::vec3(-0.5f, 0.5f, 0.0f), .TexCoords = glm::vec2(0.0f, 1.0f) },
    };
    std::vector<unsigned int> indices = { 0, 1, 3, 1, 2, 3};
    std::vector<Texture> textures = { texture };

    Mesh rect(vertices, indices, textures);

    Camera camera(SCREEN_WIDTH, SCREEN_HEIGHT, glm::vec3(0.0f, 0.0f, 2.0f));

    while(!glfwWindowShouldClose(window)) {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.use();

        camera.Matrix(45.0f, 0.1f, 100.0f, shader, "camMatrix");
        //camera.Inputs(window);

        rect.Draw(shader);

        glfwPollEvents();

        glfwSwapBuffers(window);
    }

    ResourceManager::Clear();

    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}