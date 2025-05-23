#include "story.h"

Story::Story(Character *character, int startIndex)
{
  actor = character;
  start = startIndex;
  end = startIndex;
}

void Story::update()
{
  if (actor->isMoving)
  {
    actor->move();
  }
}

void Story::append(int index, Command *command)
{
  command->execute(actor);
  commands.insert(commands.begin() + index, command);
  end = commands.size() - 1;

  if (index > end)
  {
    end = index;
  }
  else if (index < end)
  {
    Story::removeFrom(index + 1);
  }
}

int Story::undo(int index)
{
  if (Story::withinBounds(index))
  {
    int i = index - start;
    Command *command = commands.at(i);
    command->undo(actor);

    return 1;
  }
  return 0;
}

int Story::redo(int index)
{
  if (Story::withinBounds(index))
  {
    int i = index - start;
    Command *command = commands.at(i);
    command->execute(actor);

    return 1;
  }
  return 0;
}

bool Story::readyToMove()
{
  return !actor->isMoving;
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
