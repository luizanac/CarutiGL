#include "Shader.hpp"
#include <fstream>
#include <iostream>
#include "fmt/core.h"

Shader::Shader(std::string &&name, GLenum &&type) : _name(name) {
    auto loadResult = load();
    if (loadResult.getStatus() == Fail)
        throw std::invalid_argument(fmt::format("The {} file not exists", _name));

    _source = new char[loadResult.getData().length() + 1];
    std::strcpy(_source, loadResult.getData().data());

    _id = glCreateShader(type);
    if (_id == 0)
        throw std::runtime_error(fmt::format("Failed to create object shader of {}", _name));

    auto compilationResult = compile();
    if (compilationResult.getStatus() == Fail)
        throw std::runtime_error(fmt::format("Failed to compile shader {}\n{}", _name, compilationResult.getData()));
}

Result<std::string> Shader::load() {
    std::string line;
    std::string source;
    std::ifstream shaderFile(SHADER_DIRECTORY + _name);

    if (!shaderFile.is_open())
        return {source, Fail};

    while (std::getline(shaderFile, line)) {
        source.append(line + "\n");
    }

    shaderFile.close();
    return {source, Success};
}

Result<std::string> Shader::compile() {
    glShaderSource(_id, 1, &_source, nullptr);
    glCompileShader(_id);

    int success;
    char infoLog[512];
    glGetShaderiv(_id, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(_id, sizeof(infoLog), nullptr, infoLog);
        return {infoLog, Fail};
    }
    return {std::string(infoLog), Success};
}

void Shader::attachToProgram(unsigned int program) {
    _program = program;
    glAttachShader(_program, _id);
}

unsigned int Shader::getId() const {
    return _id;
}