# /Core/CMakeLists.txt

add_library(Core STATIC 
    Audio/audio_manager.cpp
    Audio/audio_manager.hpp
    
    Graphics/camera.cpp
    Graphics/camera.hpp
    Graphics/mesh.cpp
    Graphics/mesh.hpp
    Graphics/model.cpp
    Graphics/model.hpp
    Graphics/shader.cpp
    Graphics/shader.hpp
    Graphics/texture.cpp
    Graphics/texture.hpp
    
    Libs/glad.c
    Libs/glad.h
    Libs/stb_image.c
    Libs/stb_image.h

    Utils/resource_manager.cpp
    Utils/resource_manager.hpp
    Utils/window_manager.cpp
    Utils/window_manager.hpp
)

target_include_directories(Core PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

find_package(OpenGL REQUIRED)
find_package(assimp REQUIRED)

target_link_libraries(Core PUBLIC
    glfw
    OpenGL::GL
    assimp
)