#include "CaruticraftApplication.hpp"
#include "Core/Input/MouseInput.hpp"
#include "Caruticraft/Cube.hpp"
#include "Core/Skybox.hpp"

CaruticraftApplication::CaruticraftApplication(int screenWidth, int screenHeight) :
        Application(screenWidth, screenHeight),
        m_Shader("Resources/Shaders/Vertex.vert", "Resources/Shaders/Fragment.frag"),
        m_ShaderSkybox("Resources/Shaders/Skybox.vert", "Resources/Shaders/Skybox.frag") {
    glfwSetWindowTitle(m_Window, "CarutiGL - Caruticraft");
    glfwSwapInterval(0);

    m_EnvManager = new EnvironmentManager(123456u, m_Shader);

    //Creating skybox
    glGenVertexArrays(1, &m_SkyboxVAO);
    glGenBuffers(1, &m_SkyboxVBO);

    glBindVertexArray(m_SkyboxVAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_SkyboxVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Skybox::m_SkyboxVertices), &Skybox::m_SkyboxVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

    m_CubeMapTexHandle = Texture::LoadCubemap(
            {
                    "Resources/Skybox/m-right.jpg",
                    "Resources/Skybox/m-left.jpg",
                    "Resources/Skybox/m-top.jpg",
                    "Resources/Skybox/m-bottom.jpg",
                    "Resources/Skybox/m-front.jpg",
                    "Resources/Skybox/m-back.jpg"});

    m_ShaderSkybox.Use();
    m_ShaderSkybox.SetInt("skybox", 0);
    //End creating skybox
}

void CaruticraftApplication::OnUpdate() {
    UpdateCamera();
    UpdateMatrices();

    m_EnvManager->DrawChunks(10, 50, 10, 0.05);

    DrawSkybox();
}

void CaruticraftApplication::UpdateCamera() {
    if (glfwGetKey(m_Window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(m_Window, true);
    if (glfwGetKey(m_Window, GLFW_KEY_W) == GLFW_PRESS)
        m_Camera.ProcessKeyboard(FORWARD, m_DeltaTime);
    if (glfwGetKey(m_Window, GLFW_KEY_S) == GLFW_PRESS)
        m_Camera.ProcessKeyboard(BACKWARD, m_DeltaTime);
    if (glfwGetKey(m_Window, GLFW_KEY_A) == GLFW_PRESS)
        m_Camera.ProcessKeyboard(LEFT, m_DeltaTime);
    if (glfwGetKey(m_Window, GLFW_KEY_D) == GLFW_PRESS)
        m_Camera.ProcessKeyboard(RIGHT, m_DeltaTime);

    auto mousePos = MouseInput::GetMousePosition();
    float xOffset = mousePos.x - m_LastX;
    float yOffset = m_LastY - mousePos.y;

    m_LastX = mousePos.x;
    m_LastY = mousePos.y;
    m_Camera.ProcessMouseMovement(xOffset, yOffset);
}

void CaruticraftApplication::UpdateMatrices() {
    m_Shader.Use();
    m_View = m_Camera.GetViewMatrix();
    m_Shader.SetMat4("view", m_View);
    m_Shader.SetMat4("projection", m_Projection);
}

void CaruticraftApplication::DrawSkybox() {
    glDepthFunc(GL_LEQUAL);
    m_ShaderSkybox.Use();
    m_View = glm::mat4(glm::mat3(m_Camera.GetViewMatrix())); // remove translation from the view matrix
    m_ShaderSkybox.SetMat4("view", m_View);
    m_ShaderSkybox.SetMat4("projection", m_Projection);
    glBindVertexArray(m_SkyboxVAO);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, m_CubeMapTexHandle);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
    glDepthFunc(GL_LESS);
}