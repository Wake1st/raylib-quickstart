#include "stddef.h"
#include "raylib.h"
#include "input.h"

InputHandler::InputHandler()
{
  moveLeft = new MoveCommand(-GRID_SIZE, 0.0);
  moveRight = new MoveCommand(GRID_SIZE, 0.0);
  moveUp = new MoveCommand(0.0, GRID_SIZE);
  moveDown = new MoveCommand(0.0, -GRID_SIZE);
}

Command *InputHandler::handleInput()
{
  if (IsKeyDown(KEY_LEFT))
    return moveLeft;
  if (IsKeyDown(KEY_RIGHT))
    return moveRight;
  if (IsKeyDown(KEY_UP))
    return moveUp;
  if (IsKeyDown(KEY_DOWN))
    return moveDown;

  // nothing pressed
  return NULL;
}
