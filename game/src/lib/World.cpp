#include "World.hpp"


glm::vec2 World::TranslateFromWorldToScreenCoordinates(float x, float y) const {
    float localX = ((float) width - margin ) - ((float) (x * tileSize / 2) - camera->offsetX + (float) (y * tileSize / 2) - camera->offsetY) ;
    float localY = ((float) height / 2) - ((float) (y * halfTileSize / 2) - camera->offsetY - (float) (x * halfTileSize / 2) + camera->offsetX);

    return { localX, localY };
}