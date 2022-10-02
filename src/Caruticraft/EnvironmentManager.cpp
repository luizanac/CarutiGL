#include "EnvironmentManager.hpp"

EnvironmentManager::EnvironmentManager(siv::PerlinNoise::seed_type seed) {
    m_Chunks->emplace_back(new Chunk(seed, 5, 5, 5, 0.05));
    m_Chunks->emplace_back(new Chunk(seed, 5, 5, 5, 0.05, vec3(2, 1, 1)));
    m_Chunks->emplace_back(new Chunk(seed, 5, 5, 5, 0.05, vec3(1, 1, 2)));
}

void EnvironmentManager::Update(const float &deltaTime) {
    for (auto chunk: *m_Chunks) {
        chunk->SetShouldRender(Camera::Get().m_Position);
        chunk->Update(deltaTime);
    }
}


