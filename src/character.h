#pragma once

#include "raylib.h"
#include "raymath.h"

#define CLOSENESS 0.001f
#define SPEED 0.4f

class Character
{
public:
  bool isMoving;
  int movesRemaining;

  Character(Vector3 origin);
  void adjustPosition(float x, float y);
  void move();
  Vector3 getPosition();

private:
  Vector3 currentPosition;
  Vector3 targetPosition;
};
