#include <iostream>
#include <fstream>
#include <glad/glad.h>
#include "GLFW/glfw3.h"
#include "Result.hpp"
#include "Shader.hpp"

Result<GLFWwindow *> configureGlfw(int width, int height) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //Mac OS X required
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow *window = glfwCreateWindow(width, height, "CarutiGL", nullptr, nullptr);
    if (window == nullptr) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return {window, Fail};
    }
    glfwMakeContextCurrent(window);

    return {window, Success};
}

EStatus configureGlad() {
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return Fail;
    }

    return Success;
}

void frameBufferSizeCallback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f
};

int main() {
    const int width = 800, height = 600;
    Result<GLFWwindow *> glfwConfigResult = configureGlfw(width, height);
    if (glfwConfigResult.getStatus() == Fail)
        return Fail;

    EStatus gladConfigResult = configureGlad();
    if (gladConfigResult == Fail)
        return Fail;

    GLFWwindow *window = glfwConfigResult.getData();

    glfwSetFramebufferSizeCallback(window, frameBufferSizeCallback);

    Shader vertexShader("VertexShader.glsl");

    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        unsigned int vbo;
        glad_glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return Success;
}

