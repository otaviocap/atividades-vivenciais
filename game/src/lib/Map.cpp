#include "Map.hpp"
#include <glad.h>

#include "glm/gtc/type_ptr.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <iostream>

#include "glm/gtx/matrix_factorisation.hpp"
#include "Texture.hpp"
#include "VboHelper.hpp"

void Map::draw(const GLuint modelLoc, const GLuint offsetLoc, int width, int height) const {
    glBindVertexArray(this->VAO);
    glBindTexture(GL_TEXTURE_2D, this->textureId);

    for (int y = 0; y < mapRows; ++y) {
        for (int x = mapColumns-1; x >= 0 ; --x) {
            auto tile = &TILE_MAP[map[y][x]];
            auto model = glm::mat4(1);

            float localX = (float) width / 1.4 - ((float) (x * tileSize / 2) + (float) (y * tileSize / 2));
            float localY = (float) height / 1.2 - ((float) (y * halfTileSize / 2) - (float) (x * halfTileSize / 2));

            model = glm::translate(model, glm::vec3(localX, localY, 0.0));

            model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0, 0, 1));
            model = glm::scale(model, glm::vec3(scaleX, scaleY, 1.0f));

            glUniform2f(offsetLoc, (float) tile[0][0] / tileMapXSize, (float) tile[0][1] / tileMapYSize);
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, value_ptr(model));
            glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        }
    }
}

Map::Map() {
}

void Map::Initialize() {
    this->textureId = loadTexture("../../assets/tilemap.png");

    const float size = 1;

    GLuint VAO;
    glGenVertexArrays(1, &VAO);

    float yOffset = 1.0f / (float) tileMapYSize;
    float xOffset = 1.0f / (float) tileMapXSize;

    GLfloat vertices[] = {
        // x     y     z     s     t
        -0.5,  0.5, 0.0, 0.0, yOffset, //V0
        -0.5, -0.5, 0.0, 0.0, 0.0, //V1
         0.5,  0.5, 0.0, xOffset, yOffset, //V2
         0.5, -0.5, 0.0, xOffset, 0.0  //V3
    };

    for (float & vertice : vertices) {
        vertice *= size;
    }

    createVBOAndBind(VAO, vertices, std::size(vertices));

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid *) (3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    this->VAO = VAO;
}

