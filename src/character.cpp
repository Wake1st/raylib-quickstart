#include "character.h"

#define CHARACTER_HEIGHT 1.0f

Character::Character(Vector3 origin)
{
  currentPosition = origin;
  currentPosition.y = CHARACTER_HEIGHT;
  targetPosition = origin;
  isMoving = false;
}

void Character::draw(float gridSize)
{
  DrawCube(currentPosition, gridSize, gridSize, gridSize, PURPLE);
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
