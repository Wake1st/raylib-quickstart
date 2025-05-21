#pragma once

#include <vector>
#include "character.h"
#include "command.h"

class Story
{
public:
  Story(Character *character, int startIndex);
  void update();
  void append(int index, Command *cmd);
  int undo(int index);
  int redo(int index);
  bool readyToMove();
  //  TODO: splitting/rejoining actors

private:
  std::vector<Command *> commands;
  Character *actor;
  int start, end;

  bool withinBounds(int i);
  void removeFrom(int ind);
};
