#include "EnvironmentManager.hpp"

namespace Caruticraft {
    EnvironmentManager::EnvironmentManager(siv::PerlinNoise::seed_type seed) : m_Seed(seed) {
        auto factor = 0.005f;
        for (int x = 0; x < X_MAP_SIZE / X_CHUNK_SIZE; x++) {
            for (int z = 0; z < Z_MAP_SIZE / Z_CHUNK_SIZE; z++) {
                m_Chunks->emplace_back(
                        new Chunk(m_Seed, X_CHUNK_SIZE, Y_CHUNK_SIZE, Z_CHUNK_SIZE, factor, vec3(x, 0, z)));
            }
            factor = 0.005f;
        }
    }

    void EnvironmentManager::Update(const float &deltaTime) {
        auto playerPos = Camera::Get().m_Position;
        for (auto chunk: *m_Chunks) {
            auto chunkOffsetPos = vec2(chunk->m_Position.x * X_CHUNK_SIZE,
                                       chunk->m_Position.z * Z_CHUNK_SIZE);
            chunk->SetShouldRender(distance(chunkOffsetPos, vec2(playerPos.x, playerPos.z)) < 50);
            chunk->Update(deltaTime);
        }
    }
}



