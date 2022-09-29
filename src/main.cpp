#include "Core/Result.hpp"
#include "stb_image.h"
#include <glm/glm.hpp>
#include "Core/Camera.hpp"
#include "Core/Application.hpp"

using namespace Caruti;

const int ScreenWidth = 1366, ScreenHeight = 768;

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = ScreenWidth / 2.0;
float lastY = ScreenHeight / 2.0;
bool firstMouse = true;

void HandleInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
//    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
//        camera.ProcessKeyboard(FORWARD, deltaTime);
//    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
//        camera.ProcessKeyboard(BACKWARD, deltaTime);
//    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
//        camera.ProcessKeyboard(LEFT, deltaTime);
//    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
//        camera.ProcessKeyboard(RIGHT, deltaTime);
//
}

void CursorPosCallback(float xPos, float yPos) {
    if (firstMouse) {
        lastX = xPos;
        lastY = yPos;
        firstMouse = false;
    }

    float xOffset = xPos - lastX;
    float yOffset = lastY - yPos; // reversed since y-coordinates go from bottom to top

    lastX = xPos;
    lastY = yPos;
    camera.ProcessMouseMovement(xOffset, yOffset);
}

void ScrollCallback(float xOffset, float yOffset) {
    camera.ProcessMouseScroll(yOffset);
}

int main() {
    auto application = Application::Create(ScreenWidth, ScreenHeight);

    Application::SetScrollCallback(ScrollCallback);
    Application::SetCursorPosCallback(CursorPosCallback);

    Application::OnUpdate([](float deltaTime) {
        HandleInput(Application::Get().GetWindow());
        std::cout << deltaTime << std::endl;
    });

    Application::Get().Run();

    return Success;
}

