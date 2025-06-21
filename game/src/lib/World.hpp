#ifndef WORLD_HPP
#define WORLD_HPP

#include "Camera.hpp"
#include "glm/gtc/type_ptr.hpp"

class World {
int width, height;
Camera* camera;

public:
	const static int tileSize = 64;
	const static int halfTileSize = tileSize / 2;
	const static int margin = halfTileSize;

	World(const int width, const int height, Camera* camera) : width(width), height(height), camera(camera) {};
	World() : width(0), height(0) {}

    glm::vec2 TranslateFromWorldToScreenCoordinates(float x, float y) const;
};

#endif //WORLD_HPP
