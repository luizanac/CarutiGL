#ifndef CARUTIGL_CAMERA_HPP
#define CARUTIGL_CAMERA_HPP

#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>

enum ECameraMovement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float FOV = 60.0f;

class Camera {
private:
    float _yaw;
    float _pitch;

    float _movementSpeed;
    float _mouseSensitivity;
    float _fov;

    glm::vec3 _position{};
    glm::vec3 _front;
    glm::vec3 _up{};
    glm::vec3 _right{};
    glm::vec3 _worldUp{};
public:
    explicit Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
                    float yaw = YAW, float pitch = PITCH) :
            _front(glm::vec3(0.0f, 0.0f, -1.0f)),
            _movementSpeed(SPEED),
            _mouseSensitivity(SENSITIVITY),
            _fov(FOV) {

        _position = position;
        _worldUp = up;
        _yaw = yaw;
        _pitch = pitch;
        updateCameraVectors();
    }

    [[nodiscard]]glm::mat4 getViewMatrix() const;

    void processKeyboard(ECameraMovement direction, float deltaTime);

    void processMouseMovement(float xOffset, float yOffset, bool constrainPitch = true);

    void processMouseScroll(float yoffset);

    [[nodiscard]]float getFov() const;

private:
    void updateCameraVectors();
};

#endif //CARUTIGL_CAMERA_HPP
