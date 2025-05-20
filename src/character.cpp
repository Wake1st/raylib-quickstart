#include "character.h"

Character::Character(Vector3 origin, int totalMoves)
{
  currentPosition = origin;
  targetPosition = origin;
  movesRemaining = totalMoves;
  isMoving = false;
}

void Character::adjustPosition(float x, float y)
{
  targetPosition = Vector3Add(currentPosition, Vector3{x, 0.0f, -y});
}

void Character::move()
{
  currentPosition = Vector3Lerp(
      currentPosition,
      targetPosition,
      SPEED);

  float distance = Vector3Distance(currentPosition, targetPosition);
  if (distance < CLOSENESS)
  {
    currentPosition = targetPosition;
    isMoving = false;
  }
}

Vector3 Character::getPosition()
{
  return currentPosition;
}