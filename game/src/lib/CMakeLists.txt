add_library(IsometricGame_lib STATIC Map.cpp Map.hpp Sprite.cpp Sprite.hpp AnimatableSprite.hpp AnimatableSprite.cpp)
target_link_libraries(IsometricGame_lib glfw ${OPENGL_LIBS})