#ifndef SHADER_H
#define SHADER_H

#include <Libs/glad.h> 

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader {
public:
    unsigned int ID;

    Shader() { }
    Shader  &use();
    
    void    Compile(const char *vertexSource, const char *fragmentSource, const char *geometrySource = nullptr);

    void    setBool(const std::string &name, const bool value, const bool useShader = false);
    void    setInt(const std::string &name, const int value, const bool useShader = false);
    void    setFloat(const std::string &name, const float value, const bool useShader = false);
    void    setMat4(const std::string &name, const glm::mat4 &value, const bool useShader = false);
    void    setVec3f(const std::string &name, const glm::vec3 &value, const bool useShader = false);

private:
    void    checkCompileErrors(unsigned int object, std::string type);
};

#endif