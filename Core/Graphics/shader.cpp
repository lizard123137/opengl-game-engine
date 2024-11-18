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

void Shader::setBool(const std::string &name, bool value, bool useShader) {
    if (useShader)
        this->use();
    glUniform1i(glGetUniformLocation(this->ID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string &name, int value, bool useShader) {
    if (useShader)
        this->use();
    glUniform1i(glGetUniformLocation(this->ID, name.c_str()), value);
}

void Shader::setFloat(const std::string &name, float value, bool useShader) {
    if (useShader)
        this->use();
    glUniform1f(glGetUniformLocation(this->ID, name.c_str()), value);
}

void Shader::setMat4(const std::string &name, glm::mat4 value, bool useShader) {
    if (useShader)
        this->use();
    glUniformMatrix4fv(glGetUniformLocation(this->ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
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