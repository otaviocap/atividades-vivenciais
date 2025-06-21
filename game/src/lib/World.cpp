#include "World.hpp"


glm::vec2 World::TranslateFromWorldToScreenCoordinates(float x, float y) const {
    float localX = ((float) width - margin) - ((float) (x * tileSize / 2) + (float) (y * tileSize / 2));
    float localY = (float) height / 2 - ((float) (y * halfTileSize / 2) - (float) (x * halfTileSize / 2));

    return glm::vec2(localX, localY);
}