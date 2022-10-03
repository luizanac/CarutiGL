#ifndef CARUTIGL_BLOCK_HPP
#define CARUTIGL_BLOCK_HPP

#include "../Core/Graphics/Texture.hpp"
#include "../Core/Graphics/Shader.hpp"
#include "../Core/Camera.hpp"
#include <iostream>
#include "fmt/core.h"
#include "glm/glm.hpp"
#include "glm/matrix.hpp"
#include "glm/ext.hpp"

using namespace Caruti;
using namespace Caruti::Graphics;

namespace Caruticraft {

    enum EBlockType {
        Grass,
        Dirt,
        Leaves,
        OakLog
    };

    class Block : public Entity {
    private:
        Texture &m_Texture;
        Shader &m_Shader;

        EBlockType m_BlockType;

    public:
        explicit Block(vec3 position, EBlockType blockType, Shader &shader, Texture &texture) :
                m_BlockType(blockType),
                m_Shader(shader),
                m_Texture(texture) {
            m_Position = position;
        }

        void Render(vec3 chunkOffset) {
            auto newPos = m_Position + chunkOffset;
            mat4 model = translate(mat4(1.0f), newPos);
            m_Shader.SetMat4("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        void Update(const float &deltaTime) override {
        }

        constexpr static float m_Vertices[] = {
                //LEFT FACE
                -0.5, -0.5, -0.5,
                0.5, -0.5, -0.5,
                0.5, 0.5, -0.5,
                0.5, 0.5, -0.5,
                -0.5, 0.5, -0.5,
                -0.5, -0.5, -0.5,

                //RIGHT FACE
                -0.5, -0.5, 0.5,
                0.5, -0.5, 0.5,
                0.5, 0.5, 0.5,
                0.5, 0.5, 0.5,
                -0.5, 0.5, 0.5,
                -0.5, -0.5, 0.5,

                //BACK FACE
                -0.5, 0.5, 0.5,
                -0.5, 0.5, -0.5,
                -0.5, -0.5, -0.5,
                -0.5, -0.5, -0.5,
                -0.5, -0.5, 0.5,
                -0.5, 0.5, 0.5,

                //FRONT FACE
                0.5, 0.5, 0.5,
                0.5, 0.5, -0.5,
                0.5, -0.5, -0.5,
                0.5, -0.5, -0.5,
                0.5, -0.5, 0.5,
                0.5, 0.5, 0.5,

                //BOTTOM FACE
                -0.5, -0.5, -0.5,
                0.5, -0.5, -0.5,
                0.5, -0.5, 0.5,
                0.5, -0.5, 0.5,
                -0.5, -0.5, 0.5,
                -0.5, -0.5, -0.5,

                //TOP FACE
                -0.5, 0.5, -0.5,
                0.5, 0.5, -0.5,
                0.5, 0.5, 0.5,
                0.5, 0.5, 0.5,
                -0.5, 0.5, 0.5,
                -0.5, 0.5, -0.5,
        };

        constexpr static float m_GrassTexCoords[] = {
                //LEFT
                0.0, 0.75,
                0.25, 0.75,
                0.25, 1.0,
                0.25, 1.0,
                0.0, 1.0,
                0.0, 0.75,

                //RIGHT
                0.0, 0.75,
                0.25, 0.75,
                0.25, 1.0,
                0.25, 1.0,
                0.0, 1.0,
                0.0, 0.75,

                //BACK
                0.25, 1.0,
                0.0, 1.0,
                0.0, 0.75,
                0.0, 0.75,
                0.25, 0.75,
                0.25, 1.0,

                //FRONT
                0.25, 1.0,
                0.0, 1.0,
                0.0, 0.75,
                0.0, 0.75,
                0.25, 0.75,
                0.25, 1.0,

                //BOTTOM
                0.0, 0.50,
                0.25, 0.50,
                0.25, 0.75,
                0.25, 0.75,
                0.25, 0.50,
                0.0, 0.50,

                //TOP
                0.5, 0.50,
                0.75, 0.50,
                0.75, 0.75,
                0.75, 0.75,
                0.5, 0.75,
                0.5, 0.50,
        };

        constexpr static float m_OakLogTexCoords[] = {
                //LEFT
                0.0, 0.25,
                0.25, 0.25,
                0.25, 0.50,
                0.25, 0.50,
                0.0, 0.50,
                0.0, 0.25,

                //RIGHT
                0.0, 0.25,
                0.25, 0.25,
                0.25, 0.50,
                0.25, 0.50,
                0.0, 0.50,
                0.0, 0.25,

                //BACK
                0.25, 0.50,
                0.0, 0.50,
                0.0, 0.25,
                0.0, 0.25,
                0.25, 0.25,
                0.25, 0.50,

                //FRONT
                0.0, 0.50,
                0.25, 0.50,
                0.25, 0.25,
                0.25, 0.25,
                0.0, 0.25,
                0.0, 0.50,

                //BOTTOM
                0.0, 0.25,
                0.25, 0.25,
                0.25, 0.0,
                0.25, 0.0,
                0.0, 0.0,
                0.0, 0.25,

                //TOP
                0.0, 0.25,
                0.25, 0.25,
                0.25, 0.0,
                0.25, 0.0,
                0.0, 0.0,
                0.0, 0.25,
        };

    };
}

#endif //CARUTIGL_BLOCK_HPP
