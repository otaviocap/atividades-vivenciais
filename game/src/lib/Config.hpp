#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <string>
#include <vector>

/**
* File structure:
*
* tileMapFileName.png xTiles yTiles
* nonWalkableTiles
* deathTiles
* rows columns
* 0c 0 0 0 0 ...
* 0 0c 0 0 0 ...
* 0 0 0c 0 0 ...
* 0 0 0 0c 0 ...
* 0 0 0 0 0c ...
* ...
* (put a C where should be a coin)
*/
class Config {
  public:
    std::string tileMapFileName;
    int xTiles;
    int yTiles;
    std::vector<int> nonWalkableTiles;
    std::vector<int> deathTiles;

    int rows;
    int columns;
    int substituteTileId;
    std::vector<std::vector<int>> tileMap;
    std::vector<std::vector<int>> collectables;
};

class ConfigManager {
  static constexpr char delimiter = ' ';

public:
  static Config LoadConfiguration(const std::string& filePath);
};



#endif //CONFIG_HPP
