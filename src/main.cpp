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

EResultStatus configureGlad() {
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return Fail;
    }

    return Success;
}

Result<unsigned int> createProgram() {
    unsigned int program = glCreateProgram();
    int failed;
    char infoLog[512];
    glGetProgramiv(program, GL_LINK_STATUS, &failed);
    if (failed) {
        glGetProgramInfoLog(program, 512, nullptr, infoLog);
        std::cout << "Failed to create program: " << infoLog << std::endl;
        return {program, Fail};
    }

    return {program, Success};
}

void frameBufferSizeCallback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

float vertices[] = {
        -0.5f, -0.5f, 0.0f,  // left
        0.5f, -0.5f, 0.0f,  // right
        0.0f, 0.5f, 0.0f,  // top
};

int main() {
    const int width = 800, height = 600;
    Result<GLFWwindow *> glfwConfigResult = configureGlfw(width, height);
    if (glfwConfigResult.getStatus() == Fail)
        return Fail;

    EResultStatus gladConfigResult = configureGlad();
    if (gladConfigResult == Fail)
        return Fail;

    GLFWwindow *window = glfwConfigResult.getData();
    glfwSetFramebufferSizeCallback(window, frameBufferSizeCallback);

    Shader vertexShader("VertexShader.vert", GL_VERTEX_SHADER);
    Shader fragmentShader("FragmentShader.frag", GL_FRAGMENT_SHADER);

    auto programResult = createProgram();
    if (programResult.getStatus() == Fail)
        return Fail;

    auto program = programResult.getData();

    //Attach shaders to program and link them
    vertexShader.attachToProgram(program);
    fragmentShader.attachToProgram(program);
    glLinkProgram(program);

    //Create a vertex buffer object and vertex array object
    unsigned int vbo, vao;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    //Copy vertices array to a buffer for opengl use
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(program);
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteProgram(program);
    glfwTerminate();
    return Success;
}