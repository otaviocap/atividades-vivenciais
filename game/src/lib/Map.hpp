#ifndef MAP_H
#define MAP_H
#define GLM_ENABLE_EXPERIMENTAL
#include <glad.h>
#include <string>

#include "GLFW/glfw3.h"
#include "glm/gtx/transform.hpp"
#include "glm/gtc/type_ptr.hpp"

constexpr int LIGHT_GRASS_GRASS_GRID_UNSELECTED[2] = {0, 0};
constexpr int LIGHT_GRASS_GRASS_UNSELECTED[2] = {1, 0};
constexpr int LIGHT_GRASS_DIRT_GRID_UNSELECTED[2] = {2, 0};
constexpr int LIGHT_GRASS_DIRT_UNSELECTED[2] = {3, 0};
constexpr int DARK_GRASS_DIRT_GRID_UNSELECTED[2] = {4, 0};
constexpr int DARK_GRASS_DIRT_UNSELECTED[2] = {5, 0};

constexpr int LIGHT_GRASS_GRASS_GRID_SELECTED[2] = {0, 1};
constexpr int LIGHT_GRASS_GRASS_SELECTED[2] = {1, 1};
constexpr int LIGHT_GRASS_DIRT_GRID_SELECTED[2] = {2, 1};
constexpr int LIGHT_GRASS_DIRT_SELECTED[2] = {3, 1};
constexpr int DARK_GRASS_DIRT_GRID_SELECTED[2] = {4, 1};
constexpr int DARK_GRASS_DIRT_SELECTED[2] = {5, 1};

constexpr int PATH[2] = {0, 2};
constexpr int WATER[2] = {1, 2};

constexpr int ROCK[2] = {3, 2};
constexpr int FLOWER[2] = {3, 3};

constexpr int LIGHT_TREE_TOP[2] = {4, 2};
constexpr int LIGHT_TREE_BOTTOM[2] = {4, 3};

constexpr int DARK_TREE_TOP[2] = {5, 2};
constexpr int DARK_TREE_BOTTOM[2] = {5, 3};

inline const int *TILE_MAP[20] = {
    /* 0 */ LIGHT_GRASS_GRASS_GRID_UNSELECTED,
    /* 1 */ LIGHT_GRASS_GRASS_UNSELECTED,
    /* 2 */ LIGHT_GRASS_DIRT_GRID_UNSELECTED,
    /* 3 */ LIGHT_GRASS_DIRT_UNSELECTED,
    /* 4 */ DARK_GRASS_DIRT_GRID_UNSELECTED,
    /* 5 */ DARK_GRASS_DIRT_UNSELECTED,
    /* 6 */ LIGHT_GRASS_GRASS_GRID_SELECTED,
    /* 7 */ LIGHT_GRASS_GRASS_SELECTED,
    /* 8 */ LIGHT_GRASS_DIRT_GRID_SELECTED,
    /* 9 */ LIGHT_GRASS_DIRT_SELECTED,
    /* 10 */ DARK_GRASS_DIRT_GRID_SELECTED,
    /* 11 */ DARK_GRASS_DIRT_SELECTED,
    /* 12 */ PATH,
    /* 13 */ WATER,
    /* 14 */ ROCK,
    /* 15 */ FLOWER,
    /* 16 */ LIGHT_TREE_TOP,
    /* 17 */ LIGHT_TREE_BOTTOM,
    /* 18 */ DARK_TREE_TOP,
    /* 19 */ DARK_TREE_BOTTOM
};
class Map {
public:
    const int tileMapXSize = 6;
    const int tileMapYSize = 4;
    const int tileSize = 32;
    const int halfTileSize = 32 / 2;

    GLuint VAO = 0;
    GLuint textureId = 0;

    float x = 0;
    float y = 0;
    float rotation = glm::radians(180.0f);
    float scaleX = 64.0f;
    float scaleY = 64.0f;

    int mapColumns = 3;
    int mapRows = 3;


    int map[3][3] = {
        {6, 6, 13},
        {13, 6, 13},
        {13, 13, 6},
    };

    void draw(GLuint modelLoc, GLuint offsetLoc, int width, int height) const;

    Map();

    void Initialize();
};
#endif
