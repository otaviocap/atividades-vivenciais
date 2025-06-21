#define GLM_ENABLE_EXPERIMENTAL

#include <iostream>
#include <string>

#include <glad.h>
#include "GLFW/glfw3.h"
#include "glm/gtc/type_ptr.hpp"
#include "lib/Map.hpp"
#include "lib/World.hpp"

#include "lib/sprites/Sprite.hpp"
#include "lib/sprites/AnimatableSprite.hpp"
#include "shaders/BaseShader.hpp"

constexpr int WIDTH = 800;
constexpr int HEIGHT = 600;
constexpr int FPS = 4;

World world(WIDTH, HEIGHT);
AnimatableSprite character(world);
Map map(world);

void framebuffer_size_callback(GLFWwindow *window, const int width, const int height) {
    glViewport(0, 0, width, height);
}

void process_input(GLFWwindow *window) {
    const bool UpDirction = glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS;
    const bool DownDirction = glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS;
    const bool LeftDirction = glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS;
    const bool RightDirction = glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS;

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
    else if (UpDirction && LeftDirction) {
        character.changeDirection(Left);
        character.y -= 1;
    } else if (UpDirction && RightDirction) {
        character.changeDirection(Right);
        character.x += 1;
    } else if (DownDirction && LeftDirction) {
        character.changeDirection(Left);
        character.x -= 1;
    } else if (DownDirction && RightDirction) {
        character.changeDirection(Right);
        character.y += 1;

    } else if (UpDirction) {
        character.changeDirection(Up);
        character.x += 1;
        character.y -= 1;
    } else if (DownDirction) {
        character.changeDirection(Down);
        character.x -= 1;
        character.y += 1;
    } else if (LeftDirction) {
        character.changeDirection(Left);
        character.x -= 1;
        character.y -= 1;
    } else if (RightDirction) {
        character.changeDirection(Right);
        character.x += 1;
        character.y += 1;
    } else {
        character.isIdle = true;
    }
}

void generateCharacter() {
    character = AnimatableSprite(
        1,
        "../../assets/character.png",
        0,
        0,
        35,
        35,
        world,
        4,
        4
    );
}

bool validateAndStartOpenGl(GLFWwindow *&window) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwWindowHint(GLFW_SAMPLES, 8);

    window = glfwCreateWindow(WIDTH, HEIGHT, "Jogo isométrico", nullptr, nullptr);

    if (window == nullptr) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return false;
    }

    glViewport(0, 0, WIDTH, HEIGHT);
    return true;
}

int main() {
    GLFWwindow *window;

    if (!validateAndStartOpenGl(window)) {
        return -1;
    }

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    generateCharacter();
    map.Initialize();

    GLuint shaderProgram = createShaderProgram();

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

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        double currentTime = glfwGetTime();
        double deltaTime = currentTime - lastTime;

        if (deltaTime >= 1.0 / FPS) {
            process_input(window);
            character.animationFrame = !character.isIdle
                                           ? (character.animationFrame + 1) % character.animationLength
                                           : 0;
            lastTime = currentTime;
        }

        char tmp[256];
        sprintf(tmp, "Location, x: %f, y: %f", character.x, character.y);
        glfwSetWindowTitle(window, tmp);

        map.draw(modelLoc, offsetLoc, WIDTH, HEIGHT);
        character.draw(modelLoc, offsetLoc);

        glfwSwapBuffers(window);
    }

    glDeleteVertexArrays(1, &character.VAO);
    glDeleteProgram(shaderProgram);

    glfwTerminate();
    return 0;
}
