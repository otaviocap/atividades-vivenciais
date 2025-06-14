#define GLM_ENABLE_EXPERIMENTAL

#include <algorithm>
#include <iostream>
#include <string>

#include <glad.h>
#include "GLFW/glfw3.h"
#include "glm/gtx/transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "glm/gtx/matrix_factorisation.hpp"

#include "lib/Sprite.hpp"
#include "lib/AnimatableSprite.hpp"

constexpr int WIDTH = 800;
constexpr int HEIGHT = 600;
constexpr int FPS = 4;

AnimatableSprite character;

constexpr auto vertexShaderSource = R"GLSL(
 #version 400
 layout (location = 0) in vec3 position;
 layout (location = 1) in vec2 texc;
 out vec2 tex_coord;

 uniform mat4 projection;
 uniform mat4 model;

 void main()
 {
	tex_coord = vec2(texc.s, texc.t);
	gl_Position = projection * model * vec4(position, 1.0);
 }
 )GLSL";

constexpr auto fragmentShaderSource = R"GLSL(
 #version 400
 in vec2 tex_coord;
 out vec4 color;
 uniform sampler2D tex_buff;

uniform vec2 offset;

 void main()
 {
	 color = texture(tex_buff, vec2(tex_coord.x + offset.x, tex_coord.y + offset.y));
 }
 )GLSL";

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

GLuint compileShader(const char *shaderSource, int shaderType) {
    const GLuint shaderId = glCreateShader(shaderType);
    glShaderSource(shaderId, 1, &shaderSource, nullptr);
    glCompileShader(shaderId);

    int success;
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);

    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(shaderId, sizeof(infoLog), nullptr, infoLog);
        std::cout << "ERROR::SHADER::COMPILATION_FAILED\n"
                << infoLog << std::endl;
    }

    return shaderId;
}

GLuint createShaderProgram() {
    const GLuint vertexShader =
            compileShader(vertexShaderSource, GL_VERTEX_SHADER);
    const GLuint fragmentShader =
            compileShader(fragmentShaderSource, GL_FRAGMENT_SHADER);

    const GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    int success;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(shaderProgram, sizeof(infoLog), nullptr, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
                << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}

GLuint createVBOAndBind(const GLuint VAO, const float *vertices, const int verticesLength) {
    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, verticesLength * sizeof(float), vertices, GL_STATIC_DRAW);

    return VBO;
}

GLuint setupSprite(float size, int frames, int directions) {
    GLuint VAO;
    glGenVertexArrays(1, &VAO);

    float framesOffset = 1.0f / (float) frames;
    float directionOffset = 1.0f / (float) directions;

    GLfloat vertices[] = {
        // x     y     z     s     t
        -0.5,  0.5, 0.0, 0.0, directionOffset, //V0
        -0.5, -0.5, 0.0, 0.0, 0.0, //V1
         0.5,  0.5, 0.0, framesOffset, directionOffset, //V2
         0.5, -0.5, 0.0, framesOffset, 0.0  //V3
    };

    for (float & vertice : vertices) {
        vertice *= size;
    }

    createVBOAndBind(VAO, vertices, std::size(vertices));

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid *) (3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    return VAO;
}

GLuint loadTexture(const std::string &filePath) {
    GLuint texID;

    glGenTextures(1, &texID);
    glBindTexture(GL_TEXTURE_2D, texID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    int width, height, nrChannels;

    unsigned char *data = stbi_load(filePath.c_str(), &width, &height, &nrChannels, 0);

    if (data) {
        if (nrChannels == 3) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        } else // png
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        }
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load texture" << std::endl;
    }

    stbi_image_free(data);

    glBindTexture(GL_TEXTURE_2D, 0);

    return texID;
}

void generateCharacter() {
    character.x = (float) WIDTH / 2;
    character.y = (float) HEIGHT / 2;
    character.scaleX = 35;
    character.scaleY = 35;
    character.textureId = loadTexture("../../assets/character.png");

    character.VAO = setupSprite(1, 4, 4);
}

Sprite generateBackground() {
    Sprite sprite;
    sprite.x = WIDTH / 2;
    sprite.y = HEIGHT / 2;
    sprite.scaleX = WIDTH;
    sprite.scaleY = HEIGHT;

    sprite.textureId = loadTexture("../../assets/background.png");

    sprite.VAO = setupSprite(1, 1, 1);

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

    const GLuint shaderProgram = createShaderProgram();
    Sprite background = generateBackground();


    generateCharacter();

    glUseProgram(shaderProgram);
    glActiveTexture(GL_TEXTURE0);
    glUniform1i(glGetUniformLocation(shaderProgram, "tex_buff"), 0);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_ALWAYS);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    GLint offsetLoc = glGetUniformLocation(shaderProgram, "offset");
    GLint modelLoc = glGetUniformLocation(shaderProgram, "model");

    glm::mat4 projection = glm::ortho((float) WIDTH, 0.0f,  0.0f, (float) HEIGHT, -1.0f, 1.0f);
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

        if (deltaTime >= 1.0/FPS)
        {
            character.animationFrame = !character.isIdle
                ? (character.animationFrame + 1) % character.animationLength
                : 0;
            lastTime = currentTime;
        }

        background.draw(modelLoc, offsetLoc);
        character.draw(modelLoc, offsetLoc);

        glfwSwapBuffers(window);
    }

    glDeleteVertexArrays(1, &character.VAO);
    glDeleteVertexArrays(1, &background.VAO);
    glDeleteProgram(shaderProgram);

    glfwTerminate();
    return 0;
}
