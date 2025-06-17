add_library(IsometricGame_lib_shaders STATIC BaseShader.cpp BaseShader.hpp)
target_link_libraries(IsometricGame_lib_shaders glfw ${OPENGL_LIBS})