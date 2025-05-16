#include "raylib.h"

typedef struct Character
{
  bool isMoving;
  Vector3 currentPosition;
  Vector3 targetPosition;
  int movesRemaining;
  void (*move)(float, float);
} Character;