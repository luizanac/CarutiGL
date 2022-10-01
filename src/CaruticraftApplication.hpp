#ifndef CARUTIGL_CARUTICRAFTAPPLICATION_HPP
#define CARUTIGL_CARUTICRAFTAPPLICATION_HPP

#include <iostream>
#include "Core/Application.hpp"
#include "Core/Camera.hpp"
#include "Core/Graphics/Texture.hpp"
#include "Core/Graphics/Shader.hpp"
#include "../third/perlin/PerlinNoise.hpp"
#include "stb_image.h"

using namespace Caruti;

class CaruticraftApplication : public Application {
private:
    Camera m_Camera = Camera(glm::vec3(-6.0f, 8.0f, 0.0f));
    float m_LastX = (float) m_ScreenWidth / 2.0f;
    float m_LastY = (float) m_ScreenHeight / 2.0f;

    unsigned int m_VAO{}, m_VBO{}, m_SkyboxVAO{}, m_SkyboxVBO{};

    Texture m_GrassTex;
    Shader m_Shader;

    unsigned int m_CubeMapTexHandle{};
    Shader m_ShaderSkybox;

    glm::mat4 m_Model = glm::mat4(1.0f);
    glm::mat4 m_View = m_Camera.GetViewMatrix();
    glm::mat4 m_Projection = glm::perspective(
            glm::radians(m_Camera.GetFov()),
            (float) m_ScreenWidth / (float) m_ScreenHeight, 0.1f,
            200.0f);

    const siv::PerlinNoise::seed_type m_Seed = 123458u;
    const siv::PerlinNoise m_Perlin{m_Seed};

    void UpdateCamera();

    void UpdateMatrices();

    void DrawChunks();

    void DrawSkybox();

protected:
    void OnUpdate() override;

public:
    CaruticraftApplication(int screenWidth, int screenHeight);

    ~CaruticraftApplication() {
        glDeleteVertexArrays(1, &m_VAO);
        glDeleteBuffers(1, &m_VBO);

        glDeleteVertexArrays(1, &m_SkyboxVAO);
        glDeleteBuffers(1, &m_SkyboxVBO);
    }
};

#endif //CARUTIGL_CARUTICRAFTAPPLICATION_HPP
