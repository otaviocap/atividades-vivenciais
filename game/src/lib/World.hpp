#ifndef WORLD_HPP
#define WORLD_HPP

#include "Camera.hpp"
#include "glm/gtc/type_ptr.hpp"

class World {
float width, height;
Camera* camera;

public:
	constexpr static float tileSize = 64.0f;
	constexpr static float halfTileSize = tileSize / 2.0f;
	constexpr static float margin = halfTileSize;

	World(const float width, const float height, Camera* camera) : width(width), height(height), camera(camera) {};
	World() : width(0), height(0) {}

	void UpdateScreen(float width, float height);

    glm::vec2 TranslateFromWorldToScreenCoordinates(float x, float y) const;
};

#endif //WORLD_HPP
