#ifndef CARUTIGL_CARUTICRAFTAPPLICATION_HPP
#define CARUTIGL_CARUTICRAFTAPPLICATION_HPP

#include <iostream>
#include "Core/Application.hpp"
#include "Core/Camera.hpp"

#include "../third/perlin/PerlinNoise.hpp"
#include "stb_image.h"
#include "Caruticraft/EnvironmentManager.hpp"

using namespace Caruti;

class CaruticraftApplication : public Application {
private:
    Camera m_Camera = Camera(glm::vec3(-6.0f, 8.0f, 0.0f));
    float m_LastX = (float) m_ScreenWidth / 2.0f;
    float m_LastY = (float) m_ScreenHeight / 2.0f;

    Shader m_Shader;
    glm::mat4 m_View = m_Camera.GetViewMatrix();
    glm::mat4 m_Projection = glm::perspective(
            glm::radians(m_Camera.GetFov()),
            (float) m_ScreenWidth / (float) m_ScreenHeight, 0.1f,
            100.0f);

    EnvironmentManager *m_EnvManager;

    unsigned int m_SkyboxVAO{}, m_SkyboxVBO{};
    unsigned int m_CubeMapTexHandle{};
    Shader m_ShaderSkybox;


    void UpdateCamera();

    void UpdateMatrices();

    void DrawSkybox();

protected:
    void OnUpdate() override;

public:
    CaruticraftApplication(int screenWidth, int screenHeight);

    ~CaruticraftApplication() {
        delete m_EnvManager;
        glDeleteVertexArrays(1, &m_SkyboxVAO);
        glDeleteBuffers(1, &m_SkyboxVBO);
    }
};

#endif //CARUTIGL_CARUTICRAFTAPPLICATION_HPP
