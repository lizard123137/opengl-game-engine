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

    void    setBool(const std::string &name, bool value, bool useShader = false);
    void    setInt(const std::string &name, int value, bool useShader = false);
    void    setFloat(const std::string &name, float value, bool useShader = false);
    void    setMat4(const std::string &name, glm::mat4 &value, bool useShader = false);
    void    setVec3f(const std::string &name, glm::vec3 &value, bool useShader = false);

private:
    void    checkCompileErrors(unsigned int object, std::string type);
};

#endif