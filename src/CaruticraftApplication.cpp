#include "CaruticraftApplication.hpp"
#include "Core/Input/MouseInput.hpp"
#include "Caruticraft/Block.hpp"
#include "Core/Skybox.hpp"

CaruticraftApplication::CaruticraftApplication(int screenWidth, int screenHeight) :
        Application(screenWidth, screenHeight),
        m_Shader("Resources/Shaders/Vertex.vert", "Resources/Shaders/Fragment.frag"),
        m_ShaderSkybox("Resources/Shaders/Skybox.vert", "Resources/Shaders/Skybox.frag") {
    glfwSetWindowTitle(m_Window, "CarutiGL - Caruticraft");
    glfwSwapInterval(0);

    m_EnvironmentManager = new EnvironmentManager(123456u);

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

void CaruticraftApplication::Update() {
    m_EnvironmentManager->Update(m_DeltaTime);

    DrawSkybox();
    UpdateCamera();
}

void CaruticraftApplication::UpdateCamera() {
    if (glfwGetKey(m_Window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(m_Window, true);
    if (glfwGetKey(m_Window, GLFW_KEY_W) == GLFW_PRESS)
        Camera::Get().Move(FORWARD, m_DeltaTime);
    if (glfwGetKey(m_Window, GLFW_KEY_S) == GLFW_PRESS)
        Camera::Get().Move(BACKWARD, m_DeltaTime);
    if (glfwGetKey(m_Window, GLFW_KEY_A) == GLFW_PRESS)
        Camera::Get().Move(LEFT, m_DeltaTime);
    if (glfwGetKey(m_Window, GLFW_KEY_D) == GLFW_PRESS)
        Camera::Get().Move(RIGHT, m_DeltaTime);

    Camera::Get().Update(m_DeltaTime);
}


void CaruticraftApplication::DrawSkybox() {
    glDepthFunc(GL_LEQUAL);
    m_ShaderSkybox.Use();
    auto view = glm::mat4(glm::mat3(Camera::Get().GetViewMatrix())); // remove translation from the view matrix
    m_ShaderSkybox.SetMat4("view", view);
    m_ShaderSkybox.SetMat4("projection", Camera::Get().GetProjectionMatrix());
    glBindVertexArray(m_SkyboxVAO);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, m_CubeMapTexHandle);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
    glDepthFunc(GL_LESS);
}