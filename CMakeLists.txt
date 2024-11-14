cmake_minimum_required(VERSION 3.20.0)
project(opengl-game-engine VERSION 0.0.1)
cmake_policy(SET CMP0072 NEW)

find_package(OpenGL REQUIRED)

add_executable(${PROJECT_NAME} 
    src/main.cpp
    src/glad.c
    include/glad.h
)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(${PROJECT_NAME}
    glfw
    OpenGL::GL
)