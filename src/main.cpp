#include <iostream>
#include <glad/glad.h>
#include <valarray>
#include "GLFW/glfw3.h"
#include "Result.hpp"
#include "Shader.hpp"
#include "stb_image.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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

float mixValue = 0.2f;

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_UP))
        if (mixValue <= 1)
            mixValue += 0.01;

    if (glfwGetKey(window, GLFW_KEY_DOWN))
        if (mixValue >= 0)
            mixValue -= 0.01;
}


float vertices[] = {
        // positions        // texture coords
        0.5f, 0.5f, 0.0f,   1.0f, 1.0f,   // top right
        0.5f, -0.5f, 0.0f,  1.0f, 0.0f,   // bottom right
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,   // bottom left
        -0.5f, 0.5f, 0.0f,  0.0f, 1.0f    // top left
};

unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
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


    unsigned int containerTex, smileTex;
    stbi_set_flip_vertically_on_load(true);

    glGenTextures(1, &containerTex);
    glBindTexture(GL_TEXTURE_2D, containerTex);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int texWidth, texHeight, nrChannels;
    unsigned char *containerTexBuffer = stbi_load(
            "Resources/Textures/container.jpg",
            &texWidth, &texHeight,
            &nrChannels, 0);

    if (containerTexBuffer) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texWidth, texHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, containerTexBuffer);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(containerTexBuffer);

    glGenTextures(1, &smileTex);
    glBindTexture(GL_TEXTURE_2D, smileTex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int smileTexWidth, smileTexHeight, smileNrChannels;
    unsigned char *smileTexBuffer = stbi_load(
            "Resources/Textures/awesomeface.png",
            &smileTexWidth, &smileTexHeight,
            &smileNrChannels, 0);

    if (smileTexBuffer) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, smileTexWidth, smileTexHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE,
                     smileTexBuffer);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(smileTexBuffer);

    Shader shader("Resources/Shaders/VertexShader.vert",
                  "Resources/Shaders/FragmentShader.frag");

    //Create a vertex buffer object and vertex array object
    unsigned int vbo, vao, ebo;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    //Copy vertices array to a buffer for opengl use
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    //Set the vec3 in VertexShader at position 0
    //Set the size of vertex attrib that is 3
    //Set the type of the data which is GL_FLOAT
    //Set if need to normalize the data
    //set the STRIDE of 3(sum of values) * size of each element
    //The last is the offset where the position data begins in the buffer
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    shader.use();
    shader.setInt("texture1", 0);
    shader.setInt("texture2", 1);

    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, containerTex);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, smileTex);

        shader.setFloat("uMixValue", mixValue);

        glm::mat4 trans = glm::mat4(1.0f);
        trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
        trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
        trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));

        GLint transformLoc = glGetUniformLocation(shader.ProgramId, "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

        shader.use();
        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        trans = glm::mat4(1.0f);
        trans = glm::translate(trans, glm::vec3(-0.5f, 0.5f, 0.0f));
        trans = glm::scale(trans, sin(glm::vec3(1, 1, 1) * (float)glfwGetTime()));

        transformLoc = glGetUniformLocation(shader.ProgramId, "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);

    glfwTerminate();
    return Success;
}