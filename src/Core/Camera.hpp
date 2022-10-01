#ifndef CARUTIGL_CAMERA_HPP
#define CARUTIGL_CAMERA_HPP

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace Caruti {

    enum ECameraMovement {
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT
    };

    const float YAW = 80.0f;
    const float PITCH = -40.0f;
    const float SPEED = 5.5f;
    const float SENSITIVITY = 0.1f;
    const float FOV = 60.0f;

    class Camera {
    private:
        float m_Yaw;
        float m_Pitch;

        float m_MovementSpeed;
        float m_MouseSensitivity;
        float m_Fov;

        glm::vec3 m_Position{};
        glm::vec3 m_Front;
        glm::vec3 m_Up{};
        glm::vec3 m_Right{};
        glm::vec3 m_WorldUp{};
    public:
        explicit Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
                        float yaw = YAW, float pitch = PITCH) :
                m_Front(glm::vec3(0.0f, 0.0f, -1.0f)),
                m_MovementSpeed(SPEED),
                m_MouseSensitivity(SENSITIVITY),
                m_Fov(FOV) {

            m_Position = position;
            m_WorldUp = up;
            m_Yaw = yaw;
            m_Pitch = pitch;
            UpdateCameraVectors();
        }

        [[nodiscard]]glm::mat4 GetViewMatrix() const;

        void ProcessKeyboard(ECameraMovement direction, float deltaTime);

        void ProcessMouseMovement(float xOffset, float yOffset, bool constrainPitch = true);

        void ProcessMouseScroll(float yoffset);

        [[nodiscard]]float GetFov() const;

    private:
        void UpdateCameraVectors();
    };
}
#endif //CARUTIGL_CAMERA_HPP
