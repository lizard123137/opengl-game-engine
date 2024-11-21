#version 430 core

in vec2 TexCoord;
out vec4 FragColor;

uniform sampler2D image;
uniform vec3 color;

void main() {
    //FragColor = texture(image, TexCoord) * vec4(color, 1.0f);
    FragColor = vec4(color, 1.0f);
}