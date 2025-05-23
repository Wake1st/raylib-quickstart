#include "raylib.h"
#include "story_manager.h"
#include "character.h"

StoryManager::StoryManager(Vector3 startingPoint, int availableMoves)
{
  turnIndex = 0;
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
  if (currentStory->readyToMove())
  {
    // handle the input types
    Command *command = input->handleInput();
    if (command && sufficientMovesLeft())
    {
      currentStory->append(turnIndex, command);
      StoryManager::redo(true);
      turnIndex++;
      usedMoves++;
    }
    else if (input->requestingUndo())
    {
      turnIndex--;
      StoryManager::undo();
    }
    else if (input->requestingRedo())
    {
      StoryManager::redo();
      turnIndex++;
    }
    else if (input->requestingSplit())
    {
      StoryManager::createNewActor(currentStory->getActorPosition());
    }
    else if (input->requestingSwap())
    {
      StoryManager::swapActor();
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

bool StoryManager::sufficientMovesLeft()
{
  return totalMoves - usedMoves > 0;
}

void StoryManager::undo()
{
  for (Story *story : stories)
  {
    usedMoves -= story->undo(turnIndex);
  }
}

void StoryManager::redo(bool skipStory)
{
  for (Story *story : stories)
  {
    // ensure we don't move the current story
    if (!(skipStory && story == currentStory))
    {
      usedMoves += story->redo(turnIndex);
    }
  }
}

void StoryManager::createNewActor(Vector3 position)
{
  Character *actor = new Character(position);
  actors.push_back(actor);

  currentStory = new Story(actor, turnIndex);
  stories.push_back(currentStory);
  storyIndex = storyCount++;
}

void StoryManager::swapActor()
{
  // itterate and ensure bounded
  if (++storyIndex >= stories.size())
  {
    storyIndex = 0;
  }

  currentStory = stories.at(storyIndex);
}