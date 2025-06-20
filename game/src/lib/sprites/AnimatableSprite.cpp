#include "AnimatableSprite.hpp"
#include <GL/gl.h>
#include "../Texture.hpp"

AnimatableSprite::AnimatableSprite(
    const float size,
    const std::string &filePath,
    const float x,
    const float y,
    const float scaleX,
    const float scaleY,
    const int frames,
    const int directions)
    : Sprite(
        size,
        filePath,
        x,
        y,
        scaleX,
        scaleY
    ) {
    this->PostConstuct(size, frames, directions);
}

AnimatableSprite::AnimatableSprite(): Sprite() {}


void AnimatableSprite::PostConstuct(const float size, const int frames, const int directions) {
    this->Initialize(size, frames, directions);
}


void AnimatableSprite::changeDirection(const Direction direction) {
    this->isIdle = false;

    if (direction == this->direction) {
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
        directionOffset.x * (float) this->direction + this->animationOffset.x * (float) this->animationFrame,
        directionOffset.y * (float) this->direction + this->animationOffset.y * (float) this->animationFrame);
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, value_ptr(model));
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
};
