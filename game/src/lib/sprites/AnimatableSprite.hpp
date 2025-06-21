#ifndef ANIMATABLE_SPRITE_H
#define ANIMATABLE_SPRITE_H
#define GLM_ENABLE_EXPERIMENTAL

#include "Sprite.hpp"
#include <glad.h>
#include "GLFW/glfw3.h"
#include "glm/gtx/transform.hpp"
#include "glm/gtc/type_ptr.hpp"

enum Direction {
    Down = 0,
    Up = 1,
    Left = 2,
    Right = 3,
};

const int DIRECTIONS = 4;

class AnimatableSprite : public Sprite {
public:
    int animationLength = 4;

    int animationFrame = 0;
    Direction direction = Direction::Down;

    glm::vec2 directionOffset = glm::vec2(1.0f / (float) DIRECTIONS, 0.0f);
    glm::vec2 animationOffset = glm::vec2(0.0f, 1.0f / (float) animationLength);

    bool isIdle = true;

    AnimatableSprite(
        float size,
        const std::string &filePath,
        float x,
        float y,
        float scaleX,
        float scaleY,
        World world,
        int frames,
        int directions
    );

    AnimatableSprite(World world);

    void changeDirection(Direction direction);

    void draw(GLuint modelLoc, GLuint offsetLoc) const;

    void PostConstuct(float size, int frames, int directions);

};


#endif