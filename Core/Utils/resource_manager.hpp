#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <Libs/glad.h>
#include <Libs/stb_image.h>

#include <Graphics/shader.hpp>
#include <Graphics/texture.hpp>

#include <map>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

class ResourceManager {
public:
    static std::map<std::string, Shader>    Shaders;
    static std::map<std::string, Texture>   Textures;

    static Shader   LoadShader(const char *vShaderFile, const char *fShaderFile, const char *gShaderFile, std::string name);
    static Shader   &GetShader(std::string name);

    static Texture  LoadTexture(const char *file, bool alpha, std::string name);
    static Texture  &GetTexture(std::string name);

    static void     Clear();

private:
    ResourceManager() { }

    static Shader   loadShaderFromFile(const char *vShaderFile, const char *fShaderFile, const char *gShaderFile = nullptr);
    static Texture  loadTextureFromFile(const char *file, bool alpha);
};

#endif