//#include <iostream>
//#include <glad/glad.h>
//#include <valarray>
//#include "GLFW/glfw3.h"
//#include "Result.hpp"
//#include "Shader.hpp"
//#include "stb_image.h"
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include "Texture.hpp"
//#include "Cube.hpp"
//#include "Camera.hpp"
//
//const int ScreenWidth = 1366, ScreenHeight = 768;
//
//Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
//float lastX = ScreenWidth / 2.0;
//float lastY = ScreenHeight / 2.0;
//bool firstMouse = true;
//
//float deltaTime = 0.0f; // Time between current frame and last frame
//float lastFrame = 0.0f; // Time of last frame
//
//void HandleInput(GLFWwindow *window) {
//    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//        glfwSetWindowShouldClose(window, true);
//
//    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
//        camera.ProcessKeyboard(FORWARD, deltaTime);
//    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
//        camera.ProcessKeyboard(BACKWARD, deltaTime);
//    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
//        camera.ProcessKeyboard(LEFT, deltaTime);
//    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
//        camera.ProcessKeyboard(RIGHT, deltaTime);
//}
//
//void mouseCallback(GLFWwindow *window, double xPosIn, double yPosIn) {
//    auto xPos = static_cast<float>(xPosIn);
//    auto yPos = static_cast<float>(yPosIn);
//
//    if (firstMouse) {
//        lastX = xPos;
//        lastY = yPos;
//        firstMouse = false;
//    }
//
//    float xOffset = xPos - lastX;
//    float yOffset = lastY - yPos; // reversed since y-coordinates go from bottom to top
//
//    lastX = xPos;
//    lastY = yPos;
//    camera.ProcessMouseMovement(xOffset, yOffset);
//}
//
//void scrollCallback(GLFWwindow *window, double xOffset, double yOffset) {
//    camera.ProcessMouseScroll(static_cast<float>(yOffset));
//}
//
//Result<GLFWwindow *> ConfigureGlfw(int width, int height) {
//    glfwInit();
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
//
//    GLFWwindow *window = glfwCreateWindow(width, height, "CarutiGL", nullptr, nullptr);
//    if (window == nullptr) {
//        std::cout << "Failed to initialize GLFW window" << std::endl;
//        glfwTerminate();
//        return {window, Fail};
//    }
//    glfwMakeContextCurrent(window);
//
//    return {window, Success};
//}
//
//EResultStatus ConfigureGlad() {
//    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
//        std::cout << "Failed to initialize GLAD" << std::endl;
//        return Fail;
//    }
//
//    return Success;
//}
//
//void FrameBufferSizeCallback(GLFWwindow *window, int width, int height) {
//    glViewport(0, 0, width, height);
//}
//
//int main() {
//    Result<GLFWwindow *> glfwConfigResult = ConfigureGlfw(ScreenWidth, ScreenHeight);
//    if (glfwConfigResult.GetStatus() == Fail)
//        return Fail;
//
//    EResultStatus gladConfigResult = ConfigureGlad();
//    if (gladConfigResult == Fail)
//        return Fail;
//
//    GLFWwindow *window = glfwConfigResult.getData();
//    glfwSetFramebufferSizeCallback(window, FrameBufferSizeCallback);
//    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
//    glfwSetCursorPosCallback(window, mouseCallback);
//    glfwSetScrollCallback(window, scrollCallback);
//
//    Texture texContainer("Resources/Textures/container.jpg", GL_RGB);
//    Texture texSmile("Resources/Textures/awesomeface.png", GL_RGBA);
//
//    Shader shader("Resources/Shaders/VertexShader.vert", "Resources/Shaders/FragmentShader.frag");
//
//    //Create a vertex buffer object and vertex array object
//    unsigned int vbo, vao;
//    glGenBuffers(1, &vbo);
//    glGenVertexArrays(1, &vao);
//
//    //Copy vertices array to a buffer for opengl Use
//    glBindVertexArray(vao);
//    glBindBuffer(GL_ARRAY_BUFFER, vbo);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(Cube::vertices), Cube::vertices, GL_DYNAMIC_DRAW);
//
//    //Vertices map
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), nullptr);
//    glEnableVertexAttribArray(0);
//
//    //Texture map
//    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) (3 * sizeof(float)));
//    glEnableVertexAttribArray(1);
//
//    shader.Use();
//
//    texContainer.ActivateAndBind(GL_TEXTURE0);
//    texSmile.ActivateAndBind(GL_TEXTURE1);
//
//    shader.SetTexture("texture1", texContainer);
//    shader.SetTexture("texture2", texSmile);
//
//    while (!glfwWindowShouldClose(window)) {
//        auto currentFrame = (float) glfwGetTime();
//        deltaTime = currentFrame - lastFrame;
//        lastFrame = currentFrame;
//
//        HandleInput(window);
//
//        glEnable(GL_DEPTH_TEST);
//        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//        shader.Use();
//        glm::mat4 model = glm::rotate(model, (float) glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
//        glm::mat4 view = camera.GetViewMatrix();
//        glm::mat4 projection = glm::perspective(glm::radians(camera.GetFov()), (float) ScreenWidth / ScreenHeight, 0.1f,
//                                                100.0f);
//        shader.SetMat4("mode", model);
//        shader.SetMat4("view", view);
//        shader.SetMat4("projection", projection);
//
//        glBindVertexArray(vao);
//        for (auto &cubePosition: Cube::positions) {
//            //Reset identity matrix
//            model = glm::mat4(1.0f);
//            model = glm::translate(model, cubePosition);
//            model = glm::rotate(model, glm::radians((float) glfwGetTime() * 20),
//                                glm::vec3(1.0f, 0.3f, 0.5f));
//            shader.SetMat4("model", model);
//            glDrawArrays(GL_TRIANGLES, 0, 36);
//        }
//
//        glfwSwapBuffers(window);
//        glfwPollEvents();
//    }
//
//    glDeleteVertexArrays(1, &vao);
//    glDeleteBuffers(1, &vbo);
//
//    glfwTerminate();
//    return Success;
//}