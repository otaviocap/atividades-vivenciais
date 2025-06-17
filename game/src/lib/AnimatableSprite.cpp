#include "AnimatableSprite.hpp"
#include <GL/gl.h>

void AnimatableSprite::changeDirection(const Direction direction)
{
    this->isIdle = false;

    if (direction == this->direction)
    {
        return;
    }

    this->direction = direction;
    animationFrame = 0;
};

void AnimatableSprite::draw(const GLuint modelLoc, const GLuint offsetLoc) const {
    auto model = processModel();

    glBindVertexArray(this->VAO);
    glBindTexture(GL_TEXTURE_2D, this->textureId);
    glUniform2f(
        offsetLoc,
        directionOffset.x * (float)this->direction + this->animationOffset.x * (float)this->animationFrame,
        directionOffset.y * (float)this->direction + this->animationOffset.y * (float)this->animationFrame);
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, value_ptr(model));
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
};