#include "Application.hpp"

namespace Caruti {

    Application *Application::_instance = nullptr;

    Application &Application::Create(int screenWidth, int screenHeight) {
        _instance = new Application(screenWidth, screenHeight);
        return *_instance;
    }

    Application::Application(int screenWidth, int screenHeight) :
            _screenWidth(screenWidth),
            _screenHeight(screenHeight) {

        Result<GLFWwindow *> glfwConfigResult = ConfigureGlfw(_screenWidth, _screenHeight);
        if (glfwConfigResult.GetStatus() == Fail)
            exit(Fail);

        EResultStatus gladConfigResult = ConfigureGlad();
        if (gladConfigResult == Fail)
            exit(Fail);

        _window = glfwConfigResult.getData();
        glfwSetFramebufferSizeCallback(_window, FrameBufferSizeCallback);
        glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }

    void Application::UpdateDeltaTime() {
        auto currentFrame = (float) glfwGetTime();
        _deltaTime = currentFrame - _lastFrame;
        _lastFrame = currentFrame;
    }

    Result<GLFWwindow *> Application::ConfigureGlfw(int width, int height) {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

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

    void Application::SetScrollCallback(std::function<void(float, float)> &&scrollCallback) {
        Application::Get()._scrollCallback = scrollCallback;
        glfwSetScrollCallback(Application::Get().GetWindow(), [](GLFWwindow *window, double xOffset, double yOffset) {
            if (Application::Get()._scrollCallback != nullptr) {
                Application::Get()._scrollCallback((float) xOffset, (float) yOffset);
            }
        });
    }

    void Application::SetCursorPosCallback(std::function<void(float, float)> &&cursorPosCallback) {
        Application::Get()._cursorPosCallback = std::move(cursorPosCallback);
        glfwSetCursorPosCallback(Application::Get().GetWindow(), [](GLFWwindow *window, double xPos, double yPos) {
            if (Application::Get()._cursorPosCallback != nullptr) {
                Application::Get()._cursorPosCallback((float) xPos, (float) yPos);
            }
        });
    }

    void Application::OnUpdate(std::function<void(float)> updateCallback) {
        Application::Get()._onUpdate = std::move(updateCallback);
    }


    float Application::GetDeltaTime() const {
        return _deltaTime;
    }

    float Application::GetLastFrame() const {
        return _lastFrame;
    }
}