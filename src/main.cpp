#include <iostream>
#include <glad/glad.h>
#include <valarray>
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

void frameBufferSizeCallback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

float vertices[] = {
        // positions                            // colors
        0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,   // bottom right
        -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,   // bottom left
        0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f    // top
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

    Shader shader("Resources/Shaders/VertexShader.vert",
                  "Resources/Shaders/FragmentShader.frag");

    //Create a vertex buffer object and vertex array object
    unsigned int vbo, vao;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    //Copy vertices array to a buffer for opengl use
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

    //Set the vec3 in VertexShader at position 0
    //Set the size of vertex attrib that is 3
    //Set the type of the data which is GL_FLOAT
    //Set if need to normalize the data
    //set the STRIDE of 3(sum of values) * size of each element
    //The last is the offset where the position data begins in the buffer
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), nullptr);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *) (3 * sizeof(float)));
    //Enable location vec3 in VertexShader to be used
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    float lastBorderXOffset = -1;
    float xOffset = lastBorderXOffset;

    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.use();

        if (lastBorderXOffset == 1)
            xOffset -= 0.01;
        else
            xOffset += 0.01;

        if (xOffset >= 1)
            lastBorderXOffset = 1;
        else if (xOffset <= -1)
            lastBorderXOffset = -1;

        shader.setFloat("xOffset", xOffset);

        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glfwTerminate();
    return Success;
}