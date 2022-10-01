#ifndef CARUTIGL_ENVIRONMENTMANAGER_HPP
#define CARUTIGL_ENVIRONMENTMANAGER_HPP

#include "PerlinNoise.hpp"
#include "../Core/Graphics/Texture.hpp"
#include "../Core/Graphics/Shader.hpp"

using namespace Caruti;

class EnvironmentManager {
private:
    unsigned int m_VAO{}, m_VBO{};

    Texture m_GrassTex;
    Shader m_Shader;

    siv::PerlinNoise::seed_type m_Seed;
    const siv::PerlinNoise m_Perlin{m_Seed};

    void DrawChunks(const int &horizontalSize, const int &verticalSize, const int &depthSize, const float &factor);

    void UpdateMatrices();

public:
    explicit EnvironmentManager(siv::PerlinNoise::seed_type seed);

    void Update(const float &deltaTime);

    ~EnvironmentManager() {
        glDeleteVertexArrays(1, &m_VAO);
        glDeleteBuffers(1, &m_VBO);
    }

};


#endif //CARUTIGL_ENVIRONMENTMANAGER_HPP
