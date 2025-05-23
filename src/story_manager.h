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
  int storyCount;
  int totalMoves;
  int usedMoves = 0;
  int currentIndex;

  void undo();
  void redo(bool skipStory = false);
  bool sufficientMovesLeft();
};
