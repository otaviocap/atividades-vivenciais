#define GLM_ENABLE_EXPERIMENTAL

#include <iostream>
#include <string>

#include <glad.h>
#include "GLFW/glfw3.h"
#include "glm/gtc/type_ptr.hpp"
#include "lib/Map.hpp"

#include "lib/sprites/Sprite.hpp"
#include "lib/sprites/AnimatableSprite.hpp"
#include "shaders/BaseShader.hpp"

constexpr int WIDTH = 800;
constexpr int HEIGHT = 600;
constexpr int FPS = 4;

AnimatableSprite character;
Map map;

void framebuffer_size_callback(GLFWwindow *window, const int width, const int height) {
    glViewport(0, 0, width, height);
}

void process_input(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    } else if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        character.changeDirection(Up);
        character.y += 1;
    } else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        character.changeDirection(Down);
        character.y -= 1;
    } else if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        character.changeDirection(Left);
        character.x += 1;
    } else if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        character.changeDirection(Right);
        character.x -= 1;
    } else {
        character.isIdle = true;
    }
}

void generateCharacter() {
    character = AnimatableSprite(
        1,
        "../../assets/character.png",
        (float) WIDTH / 2,
        (float) HEIGHT / 2,
        35,
        35,
        4,
        4
    );
}

Sprite generateBackground() {
    const Sprite sprite(
        1,
        "../../assets/background.png",
        (float) WIDTH / 2,
        (float) HEIGHT / 2,
        (float) WIDTH,
        (float) HEIGHT);

    return sprite;
}

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwWindowHint(GLFW_SAMPLES, 8);

    GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "M5 - Personagem com animação - Otávio", nullptr, nullptr);

    if (window == nullptr) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glViewport(0, 0, WIDTH, HEIGHT);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    GLuint shaderProgram = createShaderProgram();
    Sprite background = generateBackground();

    generateCharacter();
    map.Initialize();

    glUseProgram(shaderProgram);
    glActiveTexture(GL_TEXTURE0);
    glUniform1i(glGetUniformLocation(shaderProgram, "tex_buff"), 0);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_ALWAYS);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    GLint offsetLoc = glGetUniformLocation(shaderProgram, "offset");
    GLint modelLoc = glGetUniformLocation(shaderProgram, "model");

    glm::mat4 projection = glm::ortho((float) WIDTH, 0.0f, 0.0f, (float) HEIGHT, -1.0f, 1.0f);
    glUniformMatrix4fv(
        glGetUniformLocation(shaderProgram, "projection"),
        1,
        GL_FALSE,
        value_ptr(projection)
    );

    double lastTime = glfwGetTime();

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        process_input(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        double currentTime = glfwGetTime();
        double deltaTime = currentTime - lastTime;

        if (deltaTime >= 1.0 / FPS) {
            character.animationFrame = !character.isIdle
                                           ? (character.animationFrame + 1) % character.animationLength
                                           : 0;
            lastTime = currentTime;
        }

        map.draw(modelLoc, offsetLoc, WIDTH, HEIGHT);
        // background.draw(modelLoc, offsetLoc);
        // character.draw(modelLoc, offsetLoc);

        glfwSwapBuffers(window);
    }

    glDeleteVertexArrays(1, &character.VAO);
    glDeleteVertexArrays(1, &background.VAO);
    glDeleteProgram(shaderProgram);

    glfwTerminate();
    return 0;
}
