#version 430 core

layout (location = 0) in vec2 pos;
layout (location = 1) in vec2 texPos;

out vec2 TexCoord;

uniform mat4 model;
uniform mat4 projection;

void main() {
    TexCoord = texPos;
    gl_Position = projection * model * vec4(pos, 0.0, 1.0);
}