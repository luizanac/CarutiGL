#ifndef CARUTIGL_CHUNK_HPP
#define CARUTIGL_CHUNK_HPP

#include <vector>
#include "../Core/Entity.hpp"
#include "Block.hpp"
#include "PerlinNoise.hpp"

using namespace Caruti;

namespace Caruticraft {

    class Chunk : public Entity {
    private:
        unsigned int m_VAO{}, m_VBO{};
        bool m_ShouldRender = false;

        std::vector<Block *> *m_Blocks = new std::vector<Block *>();

        Shader m_BlocksShader = Shader("Resources/Shaders/Vertex.vert", "Resources/Shaders/Fragment.frag");
        Texture m_BlocksTexture = Texture("Resources/Textures/block-texture.png", GL_RGBA);

        siv::PerlinNoise::seed_type m_Seed;
        const siv::PerlinNoise m_Perlin{m_Seed};
    public:

        Chunk(siv::PerlinNoise::seed_type seed,
              const int &horizontalSize,
              const int &verticalSize,
              const int &depthSize,
              const float &factor,
              vec3 position = vec3(1, 1, 1));

        void SetShouldRender(const vec3 &playerPosition);

        void Update(const float &deltaTime) override;

        ~Chunk() override {
            delete m_Blocks;
            glDeleteVertexArrays(1, &m_VAO);
            glDeleteBuffers(1, &m_VBO);
        }
    };
}

#endif //CARUTIGL_CHUNK_HPP
