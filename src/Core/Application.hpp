#ifndef CARUTIGL_APPLICATION_HPP
#define CARUTIGL_APPLICATION_HPP

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Result.hpp"
#include "Input/MouseInput.hpp"
#include "fmt/core.h"

namespace Caruti {

    class Application {
    protected:
        int m_ScreenWidth;
        int m_ScreenHeight;
        GLFWwindow *m_Window;
        float m_DeltaTime = 0.0f; // Time between current frame and last frame
        float m_LastFrame = 0.0f; // Time of last frame

        int m_FpsCounter{};
        double m_FrameTime{};
    public:
        Application(int screenWidth, int screenHeight);

        virtual void OnUpdate() = 0;

        void Run() {
            double lastTime = glfwGetTime();
            while (!glfwWindowShouldClose(m_Window)) {
                UpdateDeltaTime();
                auto currentTime = glfwGetTime();
                m_FpsCounter++;
                if (currentTime - lastTime >= 1.0) {
                    m_FrameTime = 1000 / double(m_FpsCounter);
                    std::cout << fmt::format("{0}FPS - {1:.2f}ms", m_FpsCounter, m_FrameTime) << std::endl;
                    m_FpsCounter = 0;
                    lastTime += 1.0;
                }
                
                glEnable(GL_DEPTH_TEST);
                glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                OnUpdate();

                MouseInput::Reset();

                glfwSwapBuffers(m_Window);
                glfwPollEvents();
            }
        }

        ~Application() {
            glfwTerminate();
        }

    private:
        void UpdateDeltaTime();

        static Result<GLFWwindow *> ConfigureGlfw(int width, int height);

        static EResultStatus ConfigureGlad();

        static void FrameBufferSizeCallback(GLFWwindow *window, int width, int height);
    };
}

#endif //CARUTIGL_APPLICATION_HPP
