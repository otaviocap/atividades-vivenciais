//
// Created by otavioh on 6/20/25.
//

#ifndef VBOHELPER_HPP
#define VBOHELPER_HPP
#include <glad.h>
#include "GLFW/glfw3.h"

GLuint createVBOAndBind(GLuint VAO, const float *vertices, int verticesLength);

#endif //VBOHELPER_HPP
