#ifndef SPRITE_H
#define SPRITE_H
#define GLM_ENABLE_EXPERIMENTAL
#include <glad.h>
#include <string>

#include "GLFW/glfw3.h"
#include "glm/gtx/transform.hpp"
#include "glm/gtc/type_ptr.hpp"

class Sprite {
public:
    GLuint VAO = 0;
    GLuint textureId = 0;

    float x = 0;
    float y = 0;
    float rotation = glm::radians(180.0f);
    float scaleX = 1.0f;
    float scaleY = 1.0f;

    glm::mat4 processModel() const;
    void draw(GLuint modelLoc, GLuint offsetLoc) const;

    Sprite(
        float size,
        const std::string &filePath,
        float x,
        float y,
        float scaleX,
        float scaleY
    );

    Sprite();

protected:
    void PostConstuct(float size);

    void Initialize(float size, int frames, int directions);

};
#endif