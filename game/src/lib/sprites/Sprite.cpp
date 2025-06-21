#include "Sprite.hpp"
#include <glad.h>

#include "glm/gtc/type_ptr.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "glm/gtx/matrix_factorisation.hpp"
#include "../Texture.hpp"
#include "../VboHelper.hpp"


glm::mat4 Sprite::processModel() const {
    auto model = glm::mat4(1);

    auto screenCoordinates = world.TranslateFromWorldToScreenCoordinates(x,y);

    model = glm::translate(model, glm::vec3(screenCoordinates, 0.0));
    model = glm::rotate(model, this->rotation, glm::vec3(0, 0, 1));
    model = glm::scale(model, glm::vec3(this->scaleX, this->scaleY, 1.0f));

    return model;
}

void Sprite::draw(const GLuint modelLoc, const GLuint offsetLoc) const {
    auto model = processModel();

    glBindVertexArray(this->VAO);
    glBindTexture(GL_TEXTURE_2D, this->textureId);
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, value_ptr(model));
    glUniform2f(offsetLoc, 0, 0);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}


Sprite::Sprite(const World world) : world(world) {}

Sprite::Sprite(
    const float size,
    const std::string &filePath,
    const float x,
    const float y,
    const float scaleX,
    const float scaleY,
    const World world
) {
    this->textureId = loadTexture(filePath);
    this->x = x;
    this->y = y;
    this->scaleX = scaleX;
    this->scaleY = scaleY;
    this->world = world;

    this->PostConstuct(size);
}

void Sprite::PostConstuct(const float size) {
    this->Initialize(size, 1, 1);
}

void Sprite::Initialize(const float size, const int frames, const int directions) {
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

    this->VAO = VAO;
}

