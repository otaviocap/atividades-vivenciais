#ifndef MAP_H
#define MAP_H
#define GLM_ENABLE_EXPERIMENTAL
#include <glad.h>
#include <string>

#include "GLFW/glfw3.h"
#include "glm/gtx/transform.hpp"
#include "glm/gtc/type_ptr.hpp"

class Map {
public:
    const int tileMapXSize = 6;
    const int tileMapYSize = 4;

    GLuint VAO = 0;
    GLuint textureId = 0;

    float x = 0;
    float y = 0;
    float rotation = glm::radians(180.0f);
    float scaleX = 1.0f;
    float scaleY = 1.0f;

    void draw(GLuint modelLoc) const;

    Map();

private:
    void Initialize();
};
#endif