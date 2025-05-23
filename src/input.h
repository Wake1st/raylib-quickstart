#pragma once

#include "command.h"
#include "character.h"

class InputHandler
{
public:
  InputHandler();
  ~InputHandler() {}
  bool requestingUndo();
  bool requestingRedo();
  bool requestingSplit();
  Command *handleInput();

private:
  Command *moveLeft;
  Command *moveRight;
  Command *moveUp;
  Command *moveDown;
};
