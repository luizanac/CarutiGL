#include "CaruticraftApplication.hpp"
#include "Core/Input/MouseInput.hpp"
#include "Caruticraft/Cube.hpp"
#include "Core/Utils.hpp"
#include "Core/Skybox.hpp"

CaruticraftApplication::CaruticraftApplication(int screenWidth, int screenHeight) :
        Application(screenWidth, screenHeight),
        m_GrassTex("Resources/Textures/block-texture.png", GL_RGBA),
        m_Shader("Resources/Shaders/Vertex.vert", "Resources/Shaders/Fragment.frag"),
        m_ShaderSkybox("Resources/Shaders/Skybox.vert", "Resources/Shaders/Skybox.frag") {

    glfwSetWindowTitle(m_Window, "CarutiGL - Caruticraft");
    glfwSwapInterval(0);

    glGenBuffers(1, &m_VBO);
    glGenVertexArrays(1, &m_VAO);
    glBindVertexArray(m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Cube::vertices), &Cube::vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);

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

    m_Shader.Use();
    m_GrassTex.ActivateAndBind(GL_TEXTURE0);
    m_Shader.SetTexture("texture1", m_GrassTex);
}


void CaruticraftApplication::OnUpdate() {
    UpdateCamera();
    UpdateMatrices();

    DrawChunks();
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
    m_Shader.SetMat4("mode", m_Model);
    m_Shader.SetMat4("view", m_View);
    m_Shader.SetMat4("projection", m_Projection);
}

void CaruticraftApplication::DrawChunks() {
    m_Shader.Use();
    m_GrassTex.ActivateAndBind(GL_TEXTURE0);
    glBindVertexArray(m_VAO);
    int horizontalSize = 50;
    float verticalSizeForce = 5.0f;
    int depthSize = 50;

    for (int x = 0; x < horizontalSize; x++) {
        for (int z = 0; z < depthSize; z++) {
            auto noiseMultiplier = Utils::Mapf(verticalSizeForce, 1, 10, 2, 20);
            auto height = (int) round(m_Perlin.noise2D(x * 0.05, z * 0.05) * noiseMultiplier);
            if (height < 0) {
                height *= -1;
            } else if (height == 0) {
                height = 1;
            }

            for (int y = 0; y < height; y++) {
                m_Model = glm::mat4(1.0f);
                m_Model = glm::translate(m_Model, glm::vec3(x, y, z));
                m_Shader.SetMat4("model", m_Model);
                glDrawArrays(GL_TRIANGLES, 0, 36);
            }
        }
    }

    glBindVertexArray(0);
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