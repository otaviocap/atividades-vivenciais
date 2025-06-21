#ifndef MAP_H
#define MAP_H
#define GLM_ENABLE_EXPERIMENTAL
#include <glad.h>

#include "Config.hpp"
#include "World.hpp"

class Map {
public:
    GLuint VAO = 0;
    GLuint textureId = 0;
    World world;

    Config* config;

    void draw(GLuint modelLoc, GLuint offsetLoc, int width, int height) const;

    Map(World w) : world(w) {};

    void Initialize(Config* config);
    void VisitTile(int x, int y);

    [[nodiscard]] bool CanMove(int x, int y) const;
};
#endif
