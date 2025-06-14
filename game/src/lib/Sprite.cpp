#include "Sprite.hpp"
#include <glad.h>

#include <algorithm>
#include <iostream>
#include <string>
#include "glm/gtx/transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "glm/gtx/matrix_factorisation.hpp"

glm::mat4 Sprite::processModel()
{
    auto model = glm::mat4(1);

    model = glm::translate(model, glm::vec3(this->x, this->y, 0.0));
    model = glm::rotate(model, this->rotation, glm::vec3(0, 0, 1));
    model = glm::scale(model, glm::vec3(this->scaleX, this->scaleY, 1.0f));

    return model;
}

void Sprite::draw(const GLuint modelLoc, const GLuint offsetLoc)
{
    auto model = processModel();

    glBindVertexArray(this->VAO);
    glBindTexture(GL_TEXTURE_2D, this->textureId);
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, value_ptr(model));
    glUniform2f(offsetLoc, 0, 0);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}