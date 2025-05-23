#include "raylib.h"
#include "story_manager.h"
#include "character.h"

StoryManager::StoryManager(Vector3 startingPoint, int availableMoves)
{
  Character *actor = new Character(startingPoint);
  actors.push_back(actor);

  currentIndex = 0;
  currentStory = new Story(actor, currentIndex);
  stories.push_back(currentStory);
  storyCount++;

  totalMoves = availableMoves;
}

StoryManager::~StoryManager()
{
  for (Character *actor : actors)
  {
    delete actor;
  }
  actors.clear();
}

void StoryManager::update(InputHandler *input)
{
  // loop through every character to move
  for (Story *story : stories)
  {
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
  for (Character *actor : actors)
  {
    DrawCube(actor->getPosition(), gridSize, gridSize, gridSize, PURPLE);
  }
}

int StoryManager::movesRemaining()
{
  return totalMoves - usedMoves;
}

void StoryManager::undo()
{
  for (Story *story : stories)
  {
    usedMoves -= story->undo(currentIndex);
  }
}

void StoryManager::redo(bool skipStory)
{
  for (Story *story : stories)
  {
    // ensure we don't move the current story
    if (!(skipStory && story == currentStory))
    {
      usedMoves += story->redo(currentIndex);
    }
  }
}

bool StoryManager::sufficientMovesLeft()
{
  return totalMoves - usedMoves > 0;
}