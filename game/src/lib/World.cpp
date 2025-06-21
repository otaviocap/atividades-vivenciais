#include "World.hpp"


void World::UpdateScreen(float width, float height) {
    this->width = width;
    this->height = height;
}

glm::vec2 World::TranslateFromWorldToScreenCoordinates(float x, float y) const {
    float localX =  width - margin -  (x * tileSize / 2.0f - camera->offsetX + (y * tileSize / 2.0f) - camera->offsetY) ;
    float localY =  height / 2.0f - (y * halfTileSize / 2.0f - camera->offsetY - (x * halfTileSize / 2.0f) + camera->offsetX);

    return { localX, localY };
}
