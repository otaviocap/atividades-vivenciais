#ifndef BASESHADER_HPP
#define BASESHADER_HPP

#include <glad.h>
GLuint compileShader(const char *shaderSource, int shaderType);
GLuint createShaderProgram();

#endif //BASESHADER_HPP
