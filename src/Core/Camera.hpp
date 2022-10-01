#ifndef CARUTIGL_CAMERA_HPP
#define CARUTIGL_CAMERA_HPP

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Entity.hpp"

namespace Caruti {

    enum ECameraMovement {
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT
    };

    const float PITCH = -40.0f;
    const float YAW = 80.0f;
    const float ROLL = 0;
    const float SPEED = 5.5f;
    const float SENSITIVITY = 0.1f;
    const float FOV = 60.0f;

    class Camera : public Entity {
    private:
        int &m_ScreenWidth;
        int &m_ScreenHeight;
        float m_MovementSpeed;
        float m_MouseSensitivity;
        float m_Fov;

        float m_LastX = (float) m_ScreenWidth / 2.0f;
        float m_LastY = (float) m_ScreenHeight / 2.0f;

        vec3 m_Front;
        vec3 m_Up{};
        vec3 m_Right{};
        vec3 m_WorldUp{};

        static Camera *m_Instance;

        explicit Camera(int &screenWidth, int &screenHeight, vec3 position, vec3 rotation, vec3 up) :
                m_ScreenWidth(screenWidth),
                m_ScreenHeight(screenHeight),
                m_Front(vec3(0.0f, 0.0f, -1.0f)),
                m_MovementSpeed(SPEED),
                m_MouseSensitivity(SENSITIVITY),
                m_Fov(FOV) {

            m_Position = position;
            m_Rotation = rotation;
            m_WorldUp = up;
            UpdateCameraVectors();
        }

    public:
        static Camera &Init(int &screenWidth, int &screenHeight,
                            vec3 position = vec3(0.0f, 0.0f, 0.0f),
                            vec3 rotation = vec3(PITCH, YAW, ROLL),
                            vec3 up = vec3(0.0f, 1.0f, 0.0f));

        static Camera &Get();

        void Update(const float &deltaTime) override;
        
        [[nodiscard]]glm::mat4 GetViewMatrix() const;

        [[nodiscard]]glm::mat4 GetProjectionMatrix() const;

        void Move(ECameraMovement direction, float deltaTime);

        void ProcessMouseMovement(float xOffset, float yOffset, bool constrainPitch = true);

        [[nodiscard]]float GetFov() const;

    private:
        void UpdateCameraVectors();

        ~Camera() override {
            delete m_Instance;
        }
    };
}
#endif //CARUTIGL_CAMERA_HPP
