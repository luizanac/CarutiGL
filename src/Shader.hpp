#ifndef CARUTIGL_SHADER_HPP
#define CARUTIGL_SHADER_HPP

#include <string>

#define SHADER_DIRECTORY "Resources/Shaders/"

class Shader {
private:
    std::string _source;
public:
    explicit Shader(std::string &&name);

    [[nodiscard]] const std::string &getSource() const;
};

#endif //CARUTIGL_SHADER_HPP
