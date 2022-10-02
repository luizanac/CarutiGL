#include <iostream>
#include "Chunk.hpp"
#include "../Core/Utils.hpp"

namespace Caruticraft {

    Chunk::Chunk(siv::PerlinNoise::seed_type seed,
                 const int &horizontalSize,
                 const int &verticalSize,
                 const int &depthSize,
                 const float &factor,
                 vec3 position) : m_Seed(seed) {
        m_Position = position;

        glGenBuffers(1, &m_VBO);
        glGenVertexArrays(1, &m_VAO);
        glBindVertexArray(m_VAO);
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Block::m_Vertices), &Block::m_Vertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), nullptr);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) (3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        m_BlocksShader.Use();
        m_BlocksTexture.ActivateAndBind(GL_TEXTURE0);
        m_BlocksShader.SetTexture("texture1", m_BlocksTexture);

        for (int x = 0; x < horizontalSize; x++) {
            for (int z = 0; z < depthSize; z++) {
                for (int y = 0; y < verticalSize; y++) {
                    auto noiseMultiplier = Utils::Mapf(x + z + y, 1, horizontalSize + depthSize + verticalSize, 1, 50);
                    auto yPos = (int) round(m_Perlin.noise3D(x * factor, y * factor, z * factor) * noiseMultiplier);
                    auto block = new Block(vec3(x, yPos, z), m_BlocksShader, m_BlocksTexture);
                    m_Blocks->push_back(block);
                }
            }
        }
    }

    void Chunk::SetShouldRender(const vec3 &playerPosition) {
        m_ShouldRender = true;
    }

    void Chunk::Update(const float &deltaTime) {
        if (!m_ShouldRender)
            return;

        glBindVertexArray(m_VAO);
        m_BlocksShader.Use();
        m_BlocksTexture.ActivateAndBind(GL_TEXTURE0);
        for (auto block: *m_Blocks) {
            block->Render(m_Position);
            block->Update(deltaTime);
        }
        glBindVertexArray(0);

        m_BlocksShader.SetMat4("view", Camera::Get().GetViewMatrix());
        m_BlocksShader.SetMat4("projection", Camera::Get().GetProjectionMatrix());
    }
}



