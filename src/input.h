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
  Command *handleInput();
  //  TODO: splitting/rejoining actors

private:
  Command *moveLeft;
  Command *moveRight;
  Command *moveUp;
  Command *moveDown;
};
