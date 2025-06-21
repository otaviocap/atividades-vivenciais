#include "Config.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

Config ConfigManager::LoadConfiguration(const std::string& filePath) {
  Config config;
  std::ifstream file(filePath);

  if (!file.is_open()) {
    std::cerr << "Could not read file " << filePath << ". File does not exist." << std::endl;
    throw std::runtime_error("Could not read configuration file " + filePath);
  }

  std::string line;
  std::getline(file, line);
  {
    std::istringstream ss(line);
    ss >> config.tileMapFileName >> config.xTiles >> config.yTiles >> config.tileWidth >> config.tileHeigth;
  }

  std::getline(file, line);
  {
    std::istringstream ss(line);
    ss >> config.substituteTileId;
  }

  std::getline(file, line);
  {
    std::istringstream ss(line);
    int val;

    while (ss >> val) {
      config.nonWalkableTiles.push_back(val);
    }
  }

  std::getline(file, line);
  {
    std::istringstream ss(line);
    int val;
    while (ss >> val) {
      config.deathTiles.push_back(val);
    }
  }

  std::getline(file, line);
  {
    std::istringstream ss(line);
    ss >> config.rows >> config.columns;
  }

  config.tileMap.resize(config.rows, std::vector<int>(config.columns, 0));
  config.collectables.resize(config.rows, std::vector<int>(config.columns, 0));

  for (int row = 0; row < config.rows; ++row) {
    if (!std::getline(file, line)) {
      throw std::runtime_error("Unexpected end of file while reading tile map.");
    }

    std::istringstream ss(line);
    for (int col = 0; col < config.columns; ++col) {
      std::string token;
      ss >> token;

      if (token.find('c') != std::string::npos) {
        token.erase(std::remove(token.begin(), token.end(), 'c'), token.end());
        config.collectables[row][col] = 1;
      }

      config.tileMap[row][col] = token.empty() ? 0 : std::stoi(token);
    }
  }

  file.close();
  return config;
}
