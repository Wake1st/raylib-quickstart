#include "raylib.h"
#include "character.h"

#define GRID_SIZE 2.0f
#define COMMAND_COUNT 16

// base class
class Command
{
public:
  virtual ~Command() {}
  virtual void execute(Character *actor) = 0;
};

class MoveCommand : public Command
{
public:
  MoveCommand(float x, float y);
  virtual void execute(Character *actor);

private:
  float x_, y_;
};
