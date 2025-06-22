#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <string>
#include <vector>

class Config {
  public:
    std::string tileMapFileName;
    int xTiles;
    int yTiles;
    int tileWidth;
    int tileHeigth;
    std::vector<int> nonWalkableTiles;
    std::vector<int> deathTiles;

    int rows;
    int columns;
    int substituteTileId;
    std::vector<std::vector<int>> tileMap;
    std::vector<std::vector<int>> collectables;

    int collectablesCount = 0;
};

class ConfigManager {
public:
  static Config LoadConfiguration(const std::string& filePath);
};



#endif //CONFIG_HPP
