#ifndef CARUTIGL_BLOCK_HPP
#define CARUTIGL_BLOCK_HPP

#include "../Core/Graphics/Texture.hpp"
#include "../Core/Graphics/Shader.hpp"
#include "../Core/Camera.hpp"
#include "glm/glm.hpp"
#include "glm/matrix.hpp"
#include "glm/ext.hpp"

using namespace Caruti;

class Block : public Entity {
private:
    Texture &m_Texture;
    Shader &m_Shader;

public:
    explicit Block(vec3 position, Shader &shader, Texture &texture) :
            m_Shader(shader),
            m_Texture(texture) {
        m_Position = position;
    }

    void Render(vec3 chunkOffset) {
        mat4 model = translate(mat4(1.0f), m_Position * chunkOffset);
        m_Shader.SetMat4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    void Update(const float &deltaTime) override {
    }

    constexpr static float m_Vertices[] = {
            -0.5, -0.5, -0.5, 0.0, 0.50,
            0.5, -0.5, -0.5, 0.25, 0.5,
            0.5, 0.5, -0.5, 0.25, 0.75,
            0.5, 0.5, -0.5, 0.25, 0.75,
            -0.5, 0.5, -0.5, 0.25, 0.50,
            -0.5, -0.5, -0.5, 0.0, 0.50,

            -0.5, -0.5, 0.5, 0.0, 0.50,
            0.5, -0.5, 0.5, 0.25, 0.50,
            0.5, 0.5, 0.5, 0.25, 0.75,
            0.5, 0.5, 0.5, 0.25, 0.75,
            -0.5, 0.5, 0.5, 0.0, 0.75,
            -0.5, -0.5, 0.5, 0.0, 0.50,

            -0.5, 0.5, 0.5, 0.25, 0.75,
            -0.5, 0.5, -0.5, 0.0, 0.75,
            -0.5, -0.5, -0.5, 0.0, 0.50,
            -0.5, -0.5, -0.5, 0.0, 0.50,
            -0.5, -0.5, 0.5, 0.25, 0.50,
            -0.5, 0.5, 0.5, 0.25, 0.75,

            0.5, 0.5, 0.5, 0.0, 0.75,
            0.5, 0.5, -0.5, 0.25, 0.75,
            0.5, -0.5, -0.5, 0.25, 0.50,
            0.5, -0.5, -0.5, 0.25, 0.50,
            0.5, -0.5, 0.5, 0.25, 0.75,
            0.5, 0.5, 0.5, 0.0, 0.75,

            -0.5, -0.5, -0.5, 0.0, 0.50,
            0.5, -0.5, -0.5, 0.25, 0.50,
            0.5, -0.5, 0.5, 0.25, 0.75,
            0.5, -0.5, 0.5, 0.25, 0.75,
            -0.5, -0.5, 0.5, 0.25, 0.50,
            -0.5, -0.5, -0.5, 0.0, 0.50,

            -0.5, 0.5, -0.5, 0.5, 0.50,
            0.5, 0.5, -0.5, 0.75, 0.50,
            0.5, 0.5, 0.5, 0.75, 0.75,
            0.5, 0.5, 0.5, 0.75, 0.75,
            -0.5, 0.5, 0.5, 0.5, 0.75,
            -0.5, 0.5, -0.5, 0.5, 0.50,
    };
};

#endif //CARUTIGL_BLOCK_HPP
