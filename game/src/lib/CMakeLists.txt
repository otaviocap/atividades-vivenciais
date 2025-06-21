add_library(IsometricGame_lib STATIC
        Map.cpp Map.hpp
        Texture.cpp Texture.hpp
        VboHelper.cpp VboHelper.hpp
        World.cpp World.hpp
        sprites/Sprite.cpp sprites/Sprite.hpp
        sprites/AnimatableSprite.cpp sprites/AnimatableSprite.hpp)

target_include_directories(IsometricGame_lib PRIVATE ${stb_image_SOURCE_DIR})
target_link_libraries(IsometricGame_lib glfw ${OPENGL_LIBS})