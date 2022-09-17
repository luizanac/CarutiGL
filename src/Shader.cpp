#include "Shader.hpp"
#include <fstream>

Shader::Shader(std::string &&name) : _name(name) {

}

Result<Shader> Shader::load() {
    std::string line;
    std::ifstream shaderFile(SHADER_DIRECTORY + _name);

    if (!shaderFile.is_open())
        return {*this, Fail};

    while (std::getline(shaderFile, line)) {
        _source.append(line);
    }

    shaderFile.close();
    return {*this, Success};
}

const std::string &Shader::getSource() const {
    return _source;
}
