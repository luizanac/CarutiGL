#include "Shader.hpp"
#include <fstream>

Shader::Shader(std::string &&name) {
    std::string line;
    std::ifstream vertexShaderFile(SHADER_DIRECTORY + name);

    if (vertexShaderFile.is_open()) {
        while (std::getline(vertexShaderFile, line)) {
            _source.append(line);
        }
        vertexShaderFile.close();
    }
}

const std::string &Shader::getSource() const {
    return _source;
}
