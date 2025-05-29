#pragma once

#include "raylib.h"
#include "story_manager.h"

// setup text
char moveText[20];
char debugText[64];

inline const char *const BoolToString(bool b)
{
  return b ? "true" : "false";
}

void draw_input_controls()
{
  sprintf(debugText, "ctrl: %s\tz: %s\ty: %s",
          BoolToString(IsKeyDown(KEY_LEFT_CONTROL)),
          BoolToString(IsKeyDown(KEY_Z)),
          BoolToString(IsKeyDown(KEY_Y)));
  DrawText(debugText, 20, 20, 20, LIGHTGRAY);
}

void draw_story_manager_data(StoryManager *storyManager)
{
  sprintf(moveText, "Moves Remaining: %d", storyManager->movesRemaining());
  DrawText(moveText, 20, 60, 20, WHITE);
}