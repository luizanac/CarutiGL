#ifndef CARUTIGL_SHADER_HPP
#define CARUTIGL_SHADER_HPP

#include <string>
#include "../Result.hpp"
#include "glad/glad.h"
#include  "glm/glm.hpp"
#include "Texture.hpp"

namespace Caruti {
    class Shader {
    private:

    private:

        static void CheckCompileErrors(unsigned int shader, const std::string &type);

    public:
        unsigned int ProgramId;

        Shader(const char *vertexPath, const char *fragmentPath);

        void Use() const;

        void SetBool(const std::string &name, bool value) const;

        void SetInt(const std::string &name, int value) const;

        void SetFloat(const std::string &name, float value) const;

        void SetMat4(const std::string &name, glm::mat4 value) const;

        void SetTexture(const char *uName, const Texture &texture);

        ~Shader() {
            glDeleteProgram(ProgramId);
        }

    };
}

#endif //CARUTIGL_SHADER_HPP
