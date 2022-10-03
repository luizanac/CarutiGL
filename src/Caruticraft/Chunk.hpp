#ifndef CARUTIGL_CHUNK_HPP
#define CARUTIGL_CHUNK_HPP

#include <vector>
#include "../Core/Entity.hpp"
#include "Block.hpp"
#include "PerlinNoise.hpp"
#include <list>

using namespace Caruti;

namespace Caruticraft {

    class Chunk : public Entity {
    private:
        int m_HorizontalSize;
        int m_VerticalSize;
        int m_DepthSize;

        unsigned int m_VAO{}, m_VerticesVBO{}, m_TexCoordsVBO{};
        bool m_ShouldRender = false;

        std::vector<Block *> *m_TerrainBlocks = new std::vector<Block *>();
        std::vector<Block *> *m_TreeBlocks = new std::vector<Block *>();

        Shader m_BlocksShader = Shader("Resources/Shaders/Vertex.vert", "Resources/Shaders/Fragment.frag");
        Texture m_BlocksTexture = Texture("Resources/Textures/block-texture.png", GL_RGBA);

        siv::PerlinNoise::seed_type m_Seed;
        const siv::PerlinNoise m_Perlin{m_Seed};
    public:

        Chunk(siv::PerlinNoise::seed_type seed,
              const int &horizontalSize,
              const int &verticalSize,
              const int &depthSize,
              float &factor,
              vec3 position = vec3(0, 0, 0));

        void SetShouldRender(bool shouldRender);

        void Update(const float &deltaTime) override;

        ~Chunk() override {
            delete m_TerrainBlocks;
            glDeleteVertexArrays(1, &m_VAO);
            glDeleteBuffers(1, &m_VerticesVBO);
            glDeleteBuffers(1, &m_TexCoordsVBO);
        }
    };
}

#endif //CARUTIGL_CHUNK_HPP
