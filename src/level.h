#pragma once

#include <vector>
#include "raylib.h"

#include "tile.h"

class Level
{
public:
  Level(float gridSize);
  ~Level();
  void draw(float gridSize);

private:
  std::vector<Tile *> tiles;
};

Level::Level(float gridSize)
{
  tiles.push_back(new PlainTile(Vector3{+0 * gridSize, -TILE_HEIGHT / 2, 0.0}));
  tiles.push_back(new PlainTile(Vector3{+1 * gridSize, -TILE_HEIGHT / 2, 0.0}));
  tiles.push_back(new PlainTile(Vector3{+2 * gridSize, -TILE_HEIGHT / 2, 0.0}));
  tiles.push_back(new PlainTile(Vector3{-1 * gridSize, -TILE_HEIGHT / 2, 0.0}));
  tiles.push_back(new PlainTile(Vector3{-2 * gridSize, -TILE_HEIGHT / 2, 0.0}));
}

Level::~Level()
{
}

void Level::draw(float gridSize)
{
  for (Tile *tile : tiles)
  {
    tile->draw(gridSize);
  }
}
