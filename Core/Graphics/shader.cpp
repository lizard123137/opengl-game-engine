#include <Graphics/shader.hpp>

void Shader::Compile(const char *vertexSource, const char *fragmentSource, const char *geometrySource) {
    unsigned int sVertex, sFragment, sGeometry;

    sVertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(sVertex, 1, &vertexSource, NULL);
    glCompileShader(sVertex);
    this->checkCompileErrors(sVertex, "VERTEX");

    sFragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(sFragment, 1, &fragmentSource, NULL);
    glCompileShader(sFragment);
    this->checkCompileErrors(sFragment, "FRAGMENT");

    if (geometrySource != nullptr) {
        sGeometry = glCreateShader(GL_GEOMETRY_SHADER);
        glShaderSource(sGeometry, 1, &geometrySource, NULL);
        glCompileShader(sGeometry);
        this->checkCompileErrors(sGeometry, "GEOMETRY");
    }

    this->ID = glCreateProgram();

    glAttachShader(this->ID, sVertex);
    glAttachShader(this->ID, sFragment);

    if (geometrySource != nullptr)
        glAttachShader(this->ID, sGeometry);

    glLinkProgram(this->ID);
    this->checkCompileErrors(this->ID, "PROGRAM");

    glDeleteShader(sVertex);
    glDeleteShader(sFragment);

    if (geometrySource != nullptr)
        glDeleteShader(sGeometry);
}

Shader &Shader::use() {
    glUseProgram(this->ID);
    return *this;
}

void Shader::setBool(const std::string &name, const bool value, const bool useShader) {
    if (useShader)
        this->use();

    GLint uniformLocation = glGetUniformLocation(this->ID, name.c_str());
    if (uniformLocation == -1)
        std::cout << "ERROR::SHADER::COULDNT_FIND_UNIFORM: " << name << std::endl;
    
    glUniform1i(uniformLocation, (int)value);
}

void Shader::setInt(const std::string &name, const int value, const bool useShader) {
    if (useShader)
        this->use();

    GLint uniformLocation = glGetUniformLocation(this->ID, name.c_str());
    if (uniformLocation == -1)
        std::cout << "ERROR::SHADER::COULDNT_FIND_UNIFORM: " << name << std::endl;

    glUniform1i(uniformLocation, value);
}

void Shader::setFloat(const std::string &name, const float value, const bool useShader) {
    if (useShader)
        this->use();
    
    GLint uniformLocation = glGetUniformLocation(this->ID, name.c_str());
    if (uniformLocation == -1)
        std::cout << "ERROR::SHADER::COULDNT_FIND_UNIFORM: " << name << std::endl;

    glUniform1f(uniformLocation, value);
}

void Shader::setMat4(const std::string &name, const glm::mat4 &value, const bool useShader) {
    if (useShader)
        this->use();
    
    GLint uniformLocation = glGetUniformLocation(this->ID, name.c_str());
    if (uniformLocation == -1)
        std::cout << "ERROR::SHADER::COULDNT_FIND_UNIFORM: " << name << std::endl;

    glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(value));
}
    
void Shader::setVec3f(const std::string &name, const glm::vec3 &value, const bool useShader) {
    if (useShader)
        this->use();
    
    GLint uniformLocation = glGetUniformLocation(this->ID, name.c_str());
    if (uniformLocation == -1)
        std::cout << "ERROR::SHADER::COULDNT_FIND_UNIFORM: " << name << std::endl;

    glUniform3f(uniformLocation, value.x, value.y, value.z);
}

void Shader::checkCompileErrors(unsigned int object, std::string type) {
    int success;
    char infoLog[1024];

    if (type != "PROGRAM") {
        glGetShaderiv(object, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(object, 1024, NULL, infoLog);
            std::cout << "| ERROR::SHADER: Compile-time error: Type: " << type << "\n"
                << infoLog << "\n -- --------------------------------------------------- -- "
                << std::endl;
        }
    } else {
        glGetProgramiv(object, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(object, 1024, NULL, infoLog);
            std::cout << "| ERROR::SHADER: Link-time error: Type: " << type << "\n"
                << infoLog << "\n -- --------------------------------------------------- -- "
                << std::endl;
        }
    }
}