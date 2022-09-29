#ifndef CARUTIGL_APPLICATION_HPP
#define CARUTIGL_APPLICATION_HPP

#include <iostream>
#include <glad/glad.h>
#include <valarray>
#include "GLFW/glfw3.h"
#include "Result.hpp"
#include "Shader.hpp"
#include "stb_image.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Texture.hpp"
#include "Cube.hpp"
#include "Camera.hpp"
#include <utility>
#include <functional>

namespace Caruti {

    class Application {
    private:
        float _deltaTime = 0.0f; // Time between current frame and last frame
        float _lastFrame = 0.0f; // Time of last frame
        int _screenWidth;
        int _screenHeight;
        GLFWwindow *_window;

        static Application *_instance;

        std::function<void(float, float)> _scrollCallback = nullptr;
        std::function<void(float, float)> _cursorPosCallback = nullptr;
        std::function<void(float)> _onUpdate = nullptr;
    public:
        static Application &Create(int screenWidth = 1920, int screenHeight = 1080);

        static Application &Get() { return *_instance; }

        GLFWwindow *GetWindow() { return _window; }

        void Run() {
            while (!glfwWindowShouldClose(_window)) {
                UpdateDeltaTime();
                if (_onUpdate != nullptr)
                    _onUpdate(_deltaTime);

                glEnable(GL_DEPTH_TEST);
                glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                glfwSwapBuffers(_window);
                glfwPollEvents();
            }
        }

        static void SetScrollCallback(std::function<void(float, float)> &&scrollCallback);

        static void SetCursorPosCallback(std::function<void(float, float)> &&cursorPosCallback);

        static void OnUpdate(std::function<void(float)> updateCallback);

        [[nodiscard]] float GetDeltaTime() const;

        [[nodiscard]] float GetLastFrame() const;

        virtual ~Application() {
            delete _instance;
            glfwTerminate();
        }


    private:
        Application(int screenWidth, int screenHeight);

        void UpdateDeltaTime();

        static Result<GLFWwindow *> ConfigureGlfw(int width, int height);

        static EResultStatus ConfigureGlad();

        static void FrameBufferSizeCallback(GLFWwindow *window, int width, int height);
    };
}

#endif //CARUTIGL_APPLICATION_HPP
