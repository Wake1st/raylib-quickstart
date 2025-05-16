#include "stddef.h"
#include "raylib.h"
#include "input.h"

class InputHandler
{
public:
  InputHandler()
  {
    moveLeft = new MoveCommand(GRID_SIZE, 0.0);
    moveRight = new MoveCommand(-GRID_SIZE, 0.0);
    moveUp = new MoveCommand(0.0, GRID_SIZE);
    moveDown = new MoveCommand(0.0, -GRID_SIZE);
  }

  Command *handleInput()
  {
    if (IsKeyDown('A'))
      return moveLeft;
    if (IsKeyDown('D'))
      return moveRight;
    if (IsKeyDown('W'))
      return moveUp;
    if (IsKeyDown('S'))
      return moveDown;

    // nothing pressed
    return NULL;
  }

private:
  Command *moveLeft;
  Command *moveRight;
  Command *moveUp;
  Command *moveDown;
};
