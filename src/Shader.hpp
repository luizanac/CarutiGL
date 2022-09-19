#ifndef CARUTIGL_SHADER_HPP
#define CARUTIGL_SHADER_HPP

#include <string>
#include "Result.hpp"
#include "glad/glad.h"

class Shader {
private:

private:

    static void checkCompileErrors(unsigned int shader, const std::string& type);
public:
    unsigned int ProgramId;

    Shader(const char *vertexPath, const char *fragmentPath);

    void use() const;

    void setBool(const std::string &name, bool value) const;

    void setInt(const std::string &name, int value) const;

    void setFloat(const std::string &name, float value) const;

    ~Shader() {
        glDeleteProgram(ProgramId);
    }

};

#endif //CARUTIGL_SHADER_HPP
