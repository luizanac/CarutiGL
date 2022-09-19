#ifndef CARUTIGL_SHADER_HPP
#define CARUTIGL_SHADER_HPP

#include <string>
#include "Result.hpp"
#include "glad/glad.h"

#define SHADER_DIRECTORY "Resources/Shaders/"

class Shader {
private:
    unsigned int _id;
    unsigned int _program = 0;
    std::string _name;
    char *_source;

    Result<std::string> load();

    Result<std::string> compile();

public:
    explicit Shader(std::string &&name, GLenum &&type);

    [[nodiscard]] unsigned int getId() const;

    void attachToProgram(unsigned int program);

    ~Shader() {
        delete _source;
        glDeleteShader(_id);
    }
};

#endif //CARUTIGL_SHADER_HPP
