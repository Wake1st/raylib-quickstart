#pragma once

#include <vector>
#include "character.h"
#include "command.h"

class Story
{
public:
  Story(Character *character, int startIndex);
  void append(int index, Command *cmd);
  void undo(int index);
  void redo(int index);

private:
  std::vector<Command *> commands;
  Character *actor;
  int start, end;

  bool withinBounds(int i);
  void removeFrom(int ind);
};
