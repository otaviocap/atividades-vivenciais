#ifndef WORLD_HPP
#define WORLD_HPP

#include "Map.hpp"
#include "sprites/AnimatableSprite.hpp"

class World {
public:
  World();

  glm::vec2 TranslateFromWorldToScreen(float x, float y);

private:
    Map map;
    AnimatableSprite character;


};

#endif //WORLD_HPP
