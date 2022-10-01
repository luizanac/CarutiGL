#ifndef CARUTIGL_CARUTICRAFTAPPLICATION_HPP
#define CARUTIGL_CARUTICRAFTAPPLICATION_HPP

#include "Core/Application.hpp"
#include "Core/Camera.hpp"
#include "Caruticraft/EnvironmentManager.hpp"

using namespace Caruti;

class CaruticraftApplication : public Application {
private:
    Shader m_Shader;

    EnvironmentManager *m_EnvironmentManager;

    unsigned int m_SkyboxVAO{}, m_SkyboxVBO{};
    unsigned int m_CubeMapTexHandle{};
    Shader m_ShaderSkybox;

    void UpdateCamera();

    void DrawSkybox();

protected:
    void Update() override;

public:
    CaruticraftApplication(int screenWidth, int screenHeight);

    ~CaruticraftApplication() {
        delete m_EnvironmentManager;
        glDeleteVertexArrays(1, &m_SkyboxVAO);
        glDeleteBuffers(1, &m_SkyboxVBO);
    }
};

#endif //CARUTIGL_CARUTICRAFTAPPLICATION_HPP
