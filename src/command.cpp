#include "command.h"

// concrete implementations
class MoveCommand : public Command
{
public:
  MoveCommand(float x, float y)
      : x_(x), y_(y) {}

  virtual void execute(Character *actor)
  {
    actor->move(x_, y_);
  }

private:
  float x_, y_;
};
