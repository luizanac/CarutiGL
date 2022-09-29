#include "Camera.hpp"

namespace Caruti {

    glm::mat4 Camera::GetViewMatrix() const {
        return glm::lookAt(_position, _position + _front, _up);
    }

    void Camera::ProcessKeyboard(ECameraMovement direction, float deltaTime) {
        float velocity = _movementSpeed * deltaTime;
        if (direction == FORWARD)
            _position += _front * velocity;
        if (direction == BACKWARD)
            _position -= _front * velocity;
        if (direction == LEFT)
            _position -= _right * velocity;
        if (direction == RIGHT)
            _position += _right * velocity;
    }

    void Camera::ProcessMouseMovement(float xOffset, float yOffset, bool constrainPitch) {
        xOffset *= _mouseSensitivity;
        yOffset *= _mouseSensitivity;

        _yaw += xOffset;
        _pitch += yOffset;

        if (constrainPitch) {
            if (_pitch > 80.0f)
                _pitch = 80.0f;
            if (_pitch < -80.0f)
                _pitch = -80.0f;
        }

        UpdateCameraVectors();
    }

    void Camera::ProcessMouseScroll(float yoffset) {
        _fov -= (float) yoffset;
        if (_fov < 1.0f)
            _fov = 1.0f;
        if (_fov > 45.0f)
            _fov = 45.0f;
    }

    void Camera::UpdateCameraVectors() {
        glm::vec3 front;
        front.x = cos(glm::radians(_yaw)) * cos(glm::radians(_pitch));
        front.y = sin(glm::radians(_pitch));
        front.z = sin(glm::radians(_yaw)) * cos(glm::radians(_pitch));

        _front = glm::normalize(front);
        _right = glm::normalize(glm::cross(_front, _worldUp));
        _up = glm::normalize(glm::cross(_right, _front));
    }

    float Camera::GetFov() const {
        return _fov;
    }

}