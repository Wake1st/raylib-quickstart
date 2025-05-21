#include "story.h"

Story::Story(Character *character, int startIndex)
{
  actor = character;
  start = startIndex;
  end = startIndex;
}

void Story::append(int index, Command *command)
{
  command->execute(actor);
  commands.push_back(command);

  if (index > end)
  {
    end = index;
  }
  else if (index < end)
  {
    Story::removeFrom(index);
  }
}

void Story::undo(int index)
{
  if (Story::withinBounds(index))
  {
    int i = index - start;
    Command *command = commands.at(i);
    command->undo(actor);
  }
}

void Story::redo(int index)
{
  if (Story::withinBounds(index))
  {
    int i = index - start;
    Command *command = commands.at(i);
    command->execute(actor);
  }
}

bool Story::withinBounds(int i)
{
  return start <= i && i <= end;
}

void Story::removeFrom(int index)
{
  int size = commands.size();
  for (int i = index; i < size; i++)
  {
    commands.pop_back();
    //  TODO: clean up command data
  }
}
