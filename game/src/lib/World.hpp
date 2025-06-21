#ifndef WORLD_HPP
#define WORLD_HPP

#include "glm/gtc/type_ptr.hpp"

class World {
int width, height;

public:
	const static int tileSize = 64;
	const static int halfTileSize = tileSize / 2;
	const static int margin = halfTileSize;

	World(const int width, const int height) : width(width), height(height) {};
	World() : width(0), height(0) {}

    glm::vec2 TranslateFromWorldToScreenCoordinates(float x, float y) const;
};

#endif //WORLD_HPP
