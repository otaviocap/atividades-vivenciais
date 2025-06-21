#ifndef MAP_H
#define MAP_H
#define GLM_ENABLE_EXPERIMENTAL
#include <glad.h>

#include "Config.hpp"
#include "World.hpp"
#include "sprites/Sprite.hpp"

class Map {
public:
    Sprite coin;

    GLuint VAO = 0;
    GLuint textureId = 0;
    World world;

    Config *config;

    void draw(GLuint modelLoc, GLuint offsetLoc);

    Map(World w) :
        world(w), coin(w) { };

    void Initialize(Config *config);

    void VisitTile(int x, int y);

    [[nodiscard]] bool CanMove(int x, int y) const;
};
#endif
