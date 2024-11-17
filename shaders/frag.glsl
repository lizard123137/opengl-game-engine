#version 330 core

out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_diffuse2;
uniform sampler2D texture_specular1;
uniform sampler2D texture_specular2;

void main() {
    /* Add support for multiple textures */
    FragColor = texture(texture_diffuse1, TexCoord);
}