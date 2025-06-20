#include "BaseShader.hpp"
#include <iostream>
#include <fstream>

const std::string readFromFile(const GLchar* pathToFile)
{
    std::string content;
    std::ifstream fileStream(pathToFile, std::ios::in);

    if(!fileStream.is_open()) {
        std::cerr << "Could not read file " << pathToFile << ". File does not exist." << std::endl;
        return "";
    }

    std::string line = "";
    while(!fileStream.eof()) {
        std::getline(fileStream, line);
        content.append(line + "\n");
    }

    fileStream.close();
    return content;
}

GLuint compileShader(const char *shaderSource, int shaderType)  {
    const GLuint shaderId = glCreateShader(shaderType);
    glShaderSource(shaderId, 1, &shaderSource, nullptr);
    glCompileShader(shaderId);

    int success;
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);

    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(shaderId, sizeof(infoLog), nullptr, infoLog);
        std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    return shaderId;
}

GLuint createShaderProgram() {
    const GLuint vertexShader = compileShader(readFromFile("../../shaders/BaseVert.vert").c_str(), GL_VERTEX_SHADER);
    const GLuint fragmentShader = compileShader(readFromFile("../../shaders/BaseFrag.frag").c_str(), GL_FRAGMENT_SHADER);

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