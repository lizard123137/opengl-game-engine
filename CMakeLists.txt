cmake_minimum_required(VERSION 3.20.0)
project(opengl-game-engine VERSION 0.0.1)

add_executable(${PROJECT_NAME} src/main.cpp)

target_link_libraries(${PROJECT_NAME} glfw)