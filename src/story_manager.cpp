#include "raylib.h"
#include "story_manager.h"
#include "character.h"

StoryManager::StoryManager(Vector3 startingPoint, int availableMoves)
{
  currentIndex = 0;
  totalMoves = availableMoves;

  StoryManager::createNewActor(startingPoint);
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
      StoryManager::redo(true);
      currentIndex++;
      usedMoves++;
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
    else if (input->requestingSplit())
    {
      StoryManager::createNewActor(currentStory->getActorPosition());
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

void StoryManager::createNewActor(Vector3 position)
{
  Character *actor = new Character(position);
  actors.push_back(actor);

  currentStory = new Story(actor, currentIndex);
  stories.push_back(currentStory);
  storyCount++;
}