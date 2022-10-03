#include <iostream>
#include "Chunk.hpp"
#include "../Core/Utils.hpp"
#include "GLFW/glfw3.h"

namespace Caruticraft {

    Chunk::Chunk(siv::PerlinNoise::seed_type seed,
                 const int &horizontalSize,
                 const int &verticalSize,
                 const int &depthSize,
                 float &factor,
                 vec3 position) : m_Seed(seed),
                                  m_HorizontalSize(horizontalSize),
                                  m_VerticalSize(verticalSize),
                                  m_DepthSize(depthSize) {
        m_Position = position;

        glGenVertexArrays(1, &m_VAO);
        glBindVertexArray(m_VAO);

        glGenBuffers(1, &m_VerticesVBO);
        glBindBuffer(GL_ARRAY_BUFFER, m_VerticesVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Block::m_Vertices), &Block::m_Vertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
        glEnableVertexAttribArray(0);

        glGenBuffers(1, &m_TexCoordsVBO);
        glBindBuffer(GL_ARRAY_BUFFER, m_TexCoordsVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Block::m_GrassTexCoords), &Block::m_GrassTexCoords, GL_DYNAMIC_DRAW);

        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), nullptr);
        glEnableVertexAttribArray(1);

        m_BlocksShader.Use();
        m_BlocksTexture.ActivateAndBind(GL_TEXTURE0);
        m_BlocksShader.SetTexture("texture1", m_BlocksTexture);

        for (int x = 0; x < horizontalSize; x++) {
            for (int z = 0; z < depthSize; z++) {
                auto noise = m_Perlin.noise2D_01(x * factor, z * factor);
                auto yPos = (int) round(Utils::Mapf((float) noise, 0, 1, 0, 6));
                m_TerrainBlocks->emplace_back(
                        new Block(vec3(x, yPos, z), EBlockType::Grass, m_BlocksShader, m_BlocksTexture));

                for (int y = yPos; y > -verticalSize; y--) {
                    m_TerrainBlocks->emplace_back(
                            new Block(vec3(x, y, z), EBlockType::Dirt, m_BlocksShader, m_BlocksTexture));
                }

                //START TREE GENERATION
                auto treeNoise = m_Perlin.noise1D_01(factor);
                auto xPos = (int) round(Utils::Mapf((float) treeNoise, 0, 1, 0, horizontalSize));
                auto zPos = (int) round(Utils::Mapf((float) treeNoise, 0, 1, 0, depthSize));

                auto lastTreePos = vec3(x, yPos, z) -= 20;
                if (!m_TreeBlocks->empty()) {
                    lastTreePos = m_TreeBlocks->at(m_TreeBlocks->size() - 1)->m_Position;
                }
                if (distance(lastTreePos, vec3(x, yPos, z)) > 5) {
                    m_TreeBlocks->emplace_back(
                            new Block(vec3(xPos, yPos + 1, zPos), EBlockType::OakLog, m_BlocksShader, m_BlocksTexture));
                    m_TreeBlocks->emplace_back(
                            new Block(vec3(xPos, yPos + 2, zPos), EBlockType::OakLog, m_BlocksShader, m_BlocksTexture));
                    m_TreeBlocks->emplace_back(
                            new Block(vec3(xPos, yPos + 3, zPos), EBlockType::OakLog, m_BlocksShader, m_BlocksTexture));
                    m_TreeBlocks->emplace_back(
                            new Block(vec3(xPos, yPos + 4, zPos), EBlockType::OakLog, m_BlocksShader, m_BlocksTexture));
                }
                //END TREE GENERATION
            }

            factor += 0.002f;
        }
    }

    void Chunk::SetShouldRender(bool shouldRender) {
        m_ShouldRender = shouldRender;
    }

    void Chunk::Update(const float &deltaTime) {
        if (!m_ShouldRender)
            return;

        glBindVertexArray(m_VAO);
        m_BlocksShader.Use();
        m_BlocksTexture.ActivateAndBind(GL_TEXTURE0);

        glBindBuffer(GL_ARRAY_BUFFER, m_TexCoordsVBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Block::m_GrassTexCoords), Block::m_GrassTexCoords);
        auto chunkOffset = vec3(m_Position.x * (float) m_HorizontalSize,
                                m_Position.y * (float) m_DepthSize,
                                m_Position.z * (float) m_DepthSize);
        for (auto block: *m_TerrainBlocks) {

            //TODO: Change this to render only blocks that will appear in the screen
            auto playerPos = Camera::Get().m_Position;
            if (distance(block->m_Position.y, playerPos.y) < 10)
                block->Render(chunkOffset);

            block->Update(deltaTime);
        }

        glBindBuffer(GL_ARRAY_BUFFER, m_TexCoordsVBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Block::m_OakLogTexCoords), Block::m_OakLogTexCoords);
        for (auto block: *m_TreeBlocks) {
            block->Render(chunkOffset);
            block->Update(deltaTime);
        }
        glBindVertexArray(0);

        m_BlocksShader.SetMat4("view", Camera::Get().GetViewMatrix());
        m_BlocksShader.SetMat4("projection", Camera::Get().GetProjectionMatrix());
    }
}



