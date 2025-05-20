#pragma once

#include "command.h"
#include "character.h"

class InputHandler
{
public:
  InputHandler();
  ~InputHandler() {}
  Command *handleInput();

private:
  Command *moveLeft;
  Command *moveRight;
  Command *moveUp;
  Command *moveDown;
};
