#pragma once

#include "raylib.h"

#define TILE_HEIGHT 0.4f

/// @brief Base class for all tiles
class Tile
{
public:
  virtual ~Tile() {}
  virtual void draw(float gridSize) = 0;
};

/// @brief Plain tile, only traversable
/// @param pos
class PlainTile : public Tile
{
public:
  PlainTile(Vector3 pos);
  virtual void draw(float gridSize);

private:
  Vector3 position;
};

PlainTile::PlainTile(Vector3 pos)
{
  position = pos;
}

void PlainTile::draw(float gridSize)
{
  DrawCube(position, gridSize, TILE_HEIGHT, gridSize, LIGHTGRAY);
}
