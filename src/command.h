#pragma once

#include "raylib.h"
#include "character.h"

#define COMMAND_COUNT 64

// base class
class Command
{
public:
  virtual ~Command() {}
  virtual void execute(Character *actor) = 0;
  virtual void undo(Character *actor) = 0;
};

class MoveCommand : public Command
{
public:
  MoveCommand(float x, float y);
  virtual void execute(Character *actor);
  virtual void undo(Character *actor);

private:
  float x_, y_;
};
