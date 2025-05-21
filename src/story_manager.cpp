#include "raylib.h"
#include "story_manager.h"
#include "character.h"

StoryManager::StoryManager(Vector3 startingPoint, int availableMoves)
{
  Character *actor = &Character(startingPoint);
  actors.push_back(actor);

  currentIndex = 0;
  currentStory = &Story(actor, currentIndex);
  stories.push_back(currentStory);
  storyCount++;

  totalMoves = availableMoves;
}

void StoryManager::update(InputHandler *input)
{
  // loop through every character to move
  for (int i = 0; i < storyCount; i++)
  {
    Story *story = stories.at(i);
    story->update();
  }

  // move the current character
  if (currentStory->readyToMove() && sufficientMovesLeft())
  {
    // handle the input types
    Command *command = input->handleInput();
    if (command)
    {
      currentStory->append(currentIndex, command);
      usedMoves++;
      StoryManager::redo(true);
      currentIndex++;
    }
    else if (input->requestingUndo())
    {
      currentIndex--;
      StoryManager::undo();
    }
    else if (input->requestingRedo())
    {
      StoryManager::redo();
      currentIndex++;
    }
  }
}

void StoryManager::draw(float gridSize)
{
  // loop through every character to move
  for (int i = 0; i < storyCount; i++)
  {
    Character *actor = actors.at(i);
    DrawCube(actor->getPosition(), gridSize, gridSize, gridSize, PURPLE);
  }
}

int StoryManager::movesRemaining()
{
  return totalMoves - usedMoves;
}

void StoryManager::undo()
{
  for (int i = 0; i < storyCount; i++)
  {
    Story *story = stories.at(i);
    usedMoves += story->undo(currentIndex);
  }
}

void StoryManager::redo(bool skipStory = false)
{
  for (int i = 0; i < storyCount; i++)
  {
    Story *story = stories.at(i);

    // ensure we don't move the current story
    if (!(skipStory && story == currentStory))
    {
      usedMoves -= story->redo(currentIndex);
    }
  }
}

bool StoryManager::sufficientMovesLeft()
{
  return totalMoves - usedMoves > 0;
}