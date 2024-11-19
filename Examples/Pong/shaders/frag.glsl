#version 430 core

in vec2 TexCoord;
out vec4 FragColor;

uniform sampler2D image;
uniform vec3 spriteColor;

void main() {
    FragColor = vec4(spriteColor, 1.0) * 1.0;
}