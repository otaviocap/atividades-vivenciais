#define GLM_ENABLE_EXPERIMENTAL

#include <iostream>
#include <string>

#include <glad.h>
#include "GLFW/glfw3.h"
#include "glm/gtc/type_ptr.hpp"
#include "lib/Config.hpp"
#include "lib/Map.hpp"
#include "lib/World.hpp"

#include "lib/sprites/Sprite.hpp"
#include "lib/sprites/AnimatableSprite.hpp"
#include "shaders/BaseShader.hpp"

int ScreenWidth = 800;
int ScreenHeight = 600;
constexpr int CHARACTER_FPS = 4;
constexpr int FPS = 60;
constexpr int MAX_MAPS = 3;
int MapCount = 0;

Config config;
Camera camera;
World world(ScreenWidth, ScreenHeight, &camera);
AnimatableSprite character(world);
Map map(world);


glm::mat4 projection;

void framebuffer_size_callback(GLFWwindow *window, const int width, const int height) {
    ScreenWidth = width;
    ScreenHeight = height;

    world.UpdateScreen(width, height);
    projection = glm::ortho((float) width, 0.0f, 0.0f, (float) height, -1.0f, 1.0f);

    glViewport(0, 0, width, height);
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

void NextMap() {
    MapCount = (MapCount + 1) % MAX_MAPS;
}

void startGame() {
    config = ConfigManager::LoadConfiguration("../../maps/map" + std::to_string(MapCount) + ".txt");
    map.Initialize(&config);
    character.x = 0.0f;
    character.y = 0.0f;
}

void process_input(GLFWwindow *window) {
    const bool UpDirection = glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS;
    const bool DownDirection = glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS;
    const bool LeftDirection = glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS;
    const bool RightDirection = glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS;
    const bool RestartKey = glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS;

    camera.x = character.x;
    camera.y = character.y;

    int tempX = character.x, tempY = character.y;

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
    else if (UpDirection && LeftDirection) {
        character.changeDirection(Left);
        tempY -= 1;
    } else if (UpDirection && RightDirection) {
        character.changeDirection(Right);
        tempX += 1;
    } else if (DownDirection && LeftDirection) {
        character.changeDirection(Left);
        tempX -= 1;
    } else if (DownDirection && RightDirection) {
        character.changeDirection(Right);
        tempY += 1;
    } else if (UpDirection) {
        character.changeDirection(Up);
        tempX += 1;
        tempY -= 1;
    } else if (DownDirection) {
        character.changeDirection(Down);
        tempX -= 1;
        tempY += 1;
    } else if (LeftDirection) {
        character.changeDirection(Left);
        tempX -= 1;
        tempY -= 1;
    } else if (RightDirection) {
        character.changeDirection(Right);
        tempX += 1;
        tempY += 1;
    } else {
        character.isIdle = true;
    }

    if (!map.CanMove(tempX, tempY) && !RestartKey) {
        return;
    }

    if (RestartKey || map.IsDeathableTile(tempX, tempY)) {
        startGame();
        return;
    }

    character.x = tempX;
    character.y = tempY;

    map.VisitTile((int) character.x, (int) character.y);

    if (map.GameHasFinished()) {
        NextMap();
        startGame();
    }
}

bool validateAndStartOpenGl(GLFWwindow *&window) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwWindowHint(GLFW_SAMPLES, 8);

    window = glfwCreateWindow(ScreenWidth, ScreenHeight, "Jogo isométrico - Bad Skeleton", nullptr, nullptr);

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

    glViewport(0, 0, ScreenWidth, ScreenHeight);
    return true;
}

double updateCharacter(GLFWwindow *window, double characterLastFrameTime) {
    double currentTime = glfwGetTime();
    double deltaTime = currentTime - characterLastFrameTime;

    if (deltaTime >= 1.0 / CHARACTER_FPS) {
        camera.process();
        process_input(window);

        character.UpdateFrame();

        return currentTime;
    }

    return characterLastFrameTime;

}

double updateCamera(GLFWwindow * window, double cameraLastFrameTime) {
    double currentTime = glfwGetTime();
    double deltaTime = currentTime - cameraLastFrameTime;

    if (deltaTime >= 1.0 / FPS) {
        camera.process();

        return currentTime;
    }

    return cameraLastFrameTime;
}


int main() {
    GLFWwindow *window;

    if (!validateAndStartOpenGl(window)) {
        return -1;
    }

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    GLuint shaderProgram = createShaderProgram();

    generateCharacter();
    startGame();

    glUseProgram(shaderProgram);
    glActiveTexture(GL_TEXTURE0);
    glUniform1i(glGetUniformLocation(shaderProgram, "tex_buff"), 0);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_ALWAYS);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    GLint offsetLoc = glGetUniformLocation(shaderProgram, "offset");
    GLint modelLoc = glGetUniformLocation(shaderProgram, "model");

    projection = glm::ortho((float) ScreenWidth, 0.0f, 0.0f, (float) ScreenHeight, -1.0f, 1.0f);
    glUniformMatrix4fv(
        glGetUniformLocation(shaderProgram, "projection"),
        1,
        GL_FALSE,
        value_ptr(projection)
    );

    double characterLastFrameTime = glfwGetTime();
    double cameraLastFrameTime = glfwGetTime();

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        characterLastFrameTime = updateCharacter(window, characterLastFrameTime);
        cameraLastFrameTime = updateCamera(window, cameraLastFrameTime);

        char tmp[256];
        sprintf(tmp, "Bad Skeleton - Location: x: %.1f, y: %.1f - Collectables: %d", character.x, character.y, map.config->collectablesCount);
        glfwSetWindowTitle(window, tmp);

        map.draw(modelLoc, offsetLoc);
        character.draw(modelLoc, offsetLoc);

        glfwSwapBuffers(window);
    }

    glDeleteVertexArrays(1, &character.VAO);
    glDeleteProgram(shaderProgram);

    glfwTerminate();
    return 0;
}
