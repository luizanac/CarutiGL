#include "Camera.hpp"

#include <cmath>

namespace Caruti {

    glm::mat4 Camera::GetViewMatrix() const {
        return glm::lookAt(m_Position, m_Position + m_Front, m_Up);
    }

    void Camera::ProcessKeyboard(ECameraMovement direction, float deltaTime) {
        float velocity = m_MovementSpeed * deltaTime;
        if (direction == FORWARD)
            m_Position += m_Front * velocity;
        if (direction == BACKWARD)
            m_Position -= m_Front * velocity;
        if (direction == LEFT)
            m_Position -= m_Right * velocity;
        if (direction == RIGHT)
            m_Position += m_Right * velocity;
    }

    void Camera::ProcessMouseMovement(float xOffset, float yOffset, bool constrainPitch) {
        xOffset *= m_MouseSensitivity;
        yOffset *= m_MouseSensitivity;

        m_Yaw += xOffset;
        m_Pitch += yOffset;

        if (constrainPitch) {
            if (m_Pitch > 80.0f)
                m_Pitch = 80.0f;
            if (m_Pitch < -80.0f)
                m_Pitch = -80.0f;
        }

        UpdateCameraVectors();
    }

    void Camera::ProcessMouseScroll(float yoffset) {
        m_Fov -= (float) yoffset;
        if (m_Fov < 1.0f)
            m_Fov = 1.0f;
        if (m_Fov > 45.0f)
            m_Fov = 45.0f;
    }

    void Camera::UpdateCameraVectors() {
        glm::vec3 front;
        front.x = (float) std::cos((float) glm::radians(m_Yaw)) * (float) cos(glm::radians(m_Pitch));
        front.y = (float) std::sin(glm::radians(m_Pitch));
        front.z = (float) std::sin((float) glm::radians(m_Yaw)) * (float) cos(glm::radians(m_Pitch));

        m_Front = glm::normalize(front);
        m_Right = glm::normalize(glm::cross(m_Front, m_WorldUp));
        m_Up = glm::normalize(glm::cross(m_Right, m_Front));
    }

    float Camera::GetFov() const {
        return m_Fov;
    }

}