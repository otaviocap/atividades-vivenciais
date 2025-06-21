#ifndef CAMERA_HPP
#define CAMERA_HPP
#include <glm/common.hpp>


class Camera {
  public:
    float offsetX = 0.0f;
    float offsetY = 0.0f;

    float x = 0.0f;
    float y = 0.0f;

    void process() {
        offsetX = glm::mix(x * 16, offsetX, 0.85);
        offsetY = glm::mix(y * 16, offsetY, 0.85);
    }

};


#endif //CAMERA_HPP
