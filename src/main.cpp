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

float interpolatedAngle = 1;
float targetAngle = 1;
float rotationSpeed = 10;

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_UP))
        if (targetAngle == 1)
            targetAngle = -1;

    if (glfwGetKey(window, GLFW_KEY_DOWN))
        if (targetAngle == -1)
            targetAngle = 1;
}

int main() {
    const int width = 1366, height = 768;
    Result<GLFWwindow *> glfwConfigResult = configureGlfw(width, height);
    if (glfwConfigResult.getStatus() == Fail)
        return Fail;

    EResultStatus gladConfigResult = configureGlad();
    if (gladConfigResult == Fail)
        return Fail;

    GLFWwindow *window = glfwConfigResult.getData();
    glfwSetFramebufferSizeCallback(window, frameBufferSizeCallback);

    Texture texContainer("Resources/Textures/container.jpg", GL_RGB);
    Texture texSmile("Resources/Textures/awesomeface.png", GL_RGBA);

    Shader shader("Resources/Shaders/VertexShader.vert", "Resources/Shaders/FragmentShader.frag");

    //Create a vertex buffer object and vertex array object
    unsigned int vbo, vao;
    glGenBuffers(1, &vbo);
    glGenVertexArrays(1, &vao);

    //Copy vertices array to a buffer for opengl use
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Cube::vertices), Cube::vertices, GL_DYNAMIC_DRAW);

    //Set the vec3 in VertexShader at position 0
    //Set the size of vertex attrib that is 3
    //Set the type of the data which is GL_FLOAT
    //Set need to normalize the data
    //set the STRIDE of 3(sum of values) * size of each element
    //The last is the offset where the position data begins in the buffer
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    shader.use();

    texContainer.activateAndBind(GL_TEXTURE0);
    texSmile.activateAndBind(GL_TEXTURE1);

    shader.setTexture("texture1", texContainer);
    shader.setTexture("texture2", texSmile);

    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        glEnable(GL_DEPTH_TEST);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.use();

        glm::mat4 transform = glm::mat4(1.0f);
        //glm::mat4 trans = glm::rotate(glm::mat4(1.0f), (float) glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
        shader.setMat4("transform", transform);

        //Create coordinate system matrices glm::radians(-55.0f)
        glm::mat4 model = glm::rotate(glm::mat4(1.0f), glm::radians(targetAngle), glm::vec3(1.0f, 0.0f, 0.0f));
        //model = glm::rotate(model, (float) glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));

        //Translating the scene in the reverse direction of where we want to move
        glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f));

        glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
        glm::vec3 cameraDirection = glm::normalize(cameraPos - Cube::positions[3]);
        glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
        glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));
        const float radius = 10.0f;
        float camX = (float) sin(glfwGetTime()) * radius;
        float camZ = (float) cos(glfwGetTime()) * radius;
        glm::vec3 cameraUp = glm::cross(cameraDirection, cameraRight);
        view = glm::lookAt(glm::vec3(camX, 0.0, camZ), Cube::positions[5], up);

        glm::mat4 projection = glm::perspective(glm::radians(60.0f), (float) width / height, 0.1f, 100.0f);

        shader.setMat4("mode", model);
        shader.setMat4("view", view);
        shader.setMat4("projection", projection);

        glBindVertexArray(vao);

        for (auto &cubePosition: Cube::positions) {
            //Reset identity matrix
            model = glm::mat4(1.0f);
            model = glm::translate(model, cubePosition);
            interpolatedAngle = std::lerp(interpolatedAngle, targetAngle, 0.0125f);
            model = glm::rotate(model, glm::radians((float) glfwGetTime() * interpolatedAngle * rotationSpeed),
                                glm::vec3(1.0f, 0.3f, 0.5f));
            shader.setMat4("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);

    glfwTerminate();
    return Success;
}