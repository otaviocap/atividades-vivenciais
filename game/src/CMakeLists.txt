add_executable(IsometricGame main.cpp ${GLAD_C_FILE})

add_subdirectory(lib)
add_subdirectory(shaders)

target_include_directories(IsometricGame PRIVATE ${CMAKE_SOURCE_DIR}/include/glad ${glm_SOURCE_DIR})
target_link_libraries(IsometricGame glfw ${OPENGL_LIBS})
target_link_libraries(IsometricGame IsometricGame_lib)
target_link_libraries(IsometricGame IsometricGame_lib_shaders)
