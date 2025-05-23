#pragma once

#include <vector>
#include "input.h"
#include "story.h"

class StoryManager
{
public:
  StoryManager(Vector3 startingPoint, int availableMoves);
  ~StoryManager();
  void update(InputHandler *input);
  void draw(float gridSize);
  int movesRemaining();

private:
  std::vector<Character *> actors;
  std::vector<Story *> stories;
  Story *currentStory;
  int storyIndex;
  int storyCount;

  int turnIndex;
  int totalMoves;
  int usedMoves = 0;

  bool sufficientMovesLeft();
  void undo();
  void redo(bool skipStory = false);
  void createNewActor(Vector3 position);
  void swapActor();
};
