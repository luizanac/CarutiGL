#include "EnvironmentManager.hpp"
#include "../Core/Utils.hpp"
#include "glm/glm.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "Cube.hpp"
#include "../Core/Camera.hpp"

EnvironmentManager::EnvironmentManager(siv::PerlinNoise::seed_type seed) :
        m_Seed(seed),
        m_Shader("Resources/Shaders/Vertex.vert", "Resources/Shaders/Fragment.frag"),
        m_GrassTex("Resources/Textures/block-texture.png", GL_RGBA) {
    glGenBuffers(1, &m_VBO);
    glGenVertexArrays(1, &m_VAO);
    glBindVertexArray(m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Cube::m_Vertices), &Cube::m_Vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    m_Shader.Use();
    m_GrassTex.ActivateAndBind(GL_TEXTURE0);
    m_Shader.SetTexture("texture1", m_GrassTex);
}

void EnvironmentManager::Update(const float &deltaTime) {
    DrawChunks(10, 50, 10, 0.05);
    UpdateMatrices();
}

void EnvironmentManager::DrawChunks(const int &horizontalSize, const int &verticalSize, const int &depthSize,
                                    const float &factor) {
    m_Shader.Use();
    m_GrassTex.ActivateAndBind(GL_TEXTURE0);
    glBindVertexArray(m_VAO);
    for (int x = 0; x < horizontalSize; x++) {
        for (int z = 0; z < depthSize; z++) {
            for (int y = 0; y < verticalSize; y++) {
                auto noiseMultiplier = Utils::Mapf(x + z + y, 1, horizontalSize + depthSize + verticalSize, 1, 50);
                auto yPos = (int) round(m_Perlin.noise3D(x * factor, y * factor, z * factor) * noiseMultiplier);
                glm::mat4 model = glm::mat4(1.0f);
                model = glm::translate(model, glm::vec3(x, yPos, z));
                m_Shader.SetMat4("model", model);
                glDrawArrays(GL_TRIANGLES, 0, 36);
            }
        }
    }

    glBindVertexArray(0);
}

void EnvironmentManager::UpdateMatrices() {
    m_Shader.Use();
    m_Shader.SetMat4("view", Camera::Get().GetViewMatrix());
    m_Shader.SetMat4("projection", Camera::Get().GetProjectionMatrix());
}


