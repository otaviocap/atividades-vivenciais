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

    for (int y = 0; y < config->rows; ++y) {
        for (int x = config->columns-1; x >= 0 ; --x) {
            auto tile = config->tileMap.at(x).at(y);
            auto model = glm::mat4(1);

            glm::vec2 worldCoordinates = world.TranslateFromWorldToScreenCoordinates(x, y);

            model = glm::translate(model, glm::vec3(worldCoordinates, 0.0));

            model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0, 0, 1));
            model = glm::scale(model, glm::vec3(config->tileWidth, config->tileHeigth, 1.0f));

            glUniform2f(offsetLoc, (float) (tile % config->xTiles) / (float) config->xTiles, (float) (tile / config->xTiles) / (float) config->yTiles);
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, value_ptr(model));
            glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        }
    }
}

void Map::Initialize(Config* config) {
    this->textureId = loadTexture("../../assets/" + config->tileMapFileName);
    this->config = config;

    const float size = 1;

    GLuint VAO;
    glGenVertexArrays(1, &VAO);

    float yOffset = 1.0f / (float) config->yTiles;
    float xOffset = 1.0f / (float) config->xTiles;

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

void Map::VisitTile(const int x, const int y) {
    config->tileMap.at(x).at(y) = config->substituteTileId;
}

bool Map::CanMove(const int x, const int y) const {
    if (x < 0 || x >= config->rows || y < 0 || y >= config->columns) {
        return false;
    }

    auto tile = config->tileMap.at(x).at(y);
    auto nonWalkable = config->nonWalkableTiles;

    if (std::find(nonWalkable.begin(), nonWalkable.end(), tile) != nonWalkable.end()) {
        return false;
    }

    return true;
}

