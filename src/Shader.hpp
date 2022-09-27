#ifndef CARUTIGL_SHADER_HPP
#define CARUTIGL_SHADER_HPP

#include <string>
#include "Result.hpp"
#include "glad/glad.h"
#include  "glm/glm.hpp"
#include "Texture.hpp"

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
    void setMat4(const std::string &name, glm::mat4 value) const;

    void setTexture(const char *uName, const Texture &texture);

    ~Shader() {
        glDeleteProgram(ProgramId);
    }

};

#endif //CARUTIGL_SHADER_HPP
