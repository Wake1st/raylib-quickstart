#include "command.h"

// concrete implementations
MoveCommand::MoveCommand(float x, float y) : x_(x), y_(y) {}

void MoveCommand::execute(Character *actor)
{
  actor->adjustPosition(x_, y_);
  actor->isMoving = true;
  actor->movesRemaining--;
}

void MoveCommand::undo(Character *actor)
{
  actor->adjustPosition(-x_, -y_);
  actor->isMoving = true;
  actor->movesRemaining++;
}
