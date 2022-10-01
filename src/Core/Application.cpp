#include <iostream>
#include "Application.hpp"

namespace Caruti {

    Application::Application(int screenWidth, int screenHeight) :
            m_ScreenWidth(screenWidth),
            m_ScreenHeight(screenHeight) {

        Result<GLFWwindow *> glfwConfigResult = ConfigureGlfw(m_ScreenWidth, m_ScreenHeight);
        if (glfwConfigResult.GetStatus() == Fail)
            exit(Fail);

        EResultStatus gladConfigResult = ConfigureGlad();
        if (gladConfigResult == Fail)
            exit(Fail);

        m_Window = glfwConfigResult.getData();
        glfwSetFramebufferSizeCallback(m_Window, FrameBufferSizeCallback);
        glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        MouseInput::Init(m_Window);
    }

    void Application::UpdateDeltaTime() {
        auto currentFrame = (float) glfwGetTime();
        m_DeltaTime = currentFrame - m_LastFrame;
        m_LastFrame = currentFrame;
    }

    Result<GLFWwindow *> Application::ConfigureGlfw(int width, int height) {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
//        glfwWindowHint(GLFW_SAMPLES, 16);

        GLFWwindow *window = glfwCreateWindow(width, height, "CarutiGL", nullptr, nullptr);
        if (window == nullptr) {
            std::cout << "Failed to initialize GLFW window" << std::endl;
            glfwTerminate();
            return {window, Fail};
        }
        glfwMakeContextCurrent(window);

        return {window, Success};
    }

    EResultStatus Application::ConfigureGlad() {
        if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
            std::cout << "Failed to initialize GLAD" << std::endl;
            return Fail;
        }

        return Success;
    }

    void Application::FrameBufferSizeCallback(GLFWwindow *window, int width, int height) {
        glViewport(0, 0, width, height);
    }
}