# /Examples/Pong/CmakeLists.txt

add_executable(pong-example
    src/main.cpp
    src/ball.cpp
    src/inputs.cpp
    src/paddle.cpp
)

target_link_libraries(pong-example PRIVATE Core)
