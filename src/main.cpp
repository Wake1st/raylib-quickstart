/*
Raylib example file.
This is an example main file for a simple raylib project.
Use this as a starting point or replace it with your code.

by Jeffery Myers is marked with CC0 1.0. To view a copy of this license, visit https://creativecommons.org/publicdomain/zero/1.0/

*/

#include "stdio.h"
#include "stdlib.h"
#include "raylib.h"
#include "raymath.h"

#include "character.h"
#include "command.h"
#include "input.h"
#include "story_manager.h"

#include "level.h"

#include "dev/debug_text.h"

int main()
{
	// Tell the window to use vsync and work on high DPI displays
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	// Create the window and OpenGL context
	InitWindow(1280, 800, "Hello Raylib");

	// setup a 3D camera
	Vector3 originPoint = Vector3{0.0f, 0.0f, 0.0f};
	Camera3D mainCamera = {0};
	mainCamera.position = Vector3{0.0f, 10.0f, 10.0f};
	mainCamera.target = originPoint;
	mainCamera.up = Vector3{0.0f, 1.0f, 0.0f};
	mainCamera.fovy = 45.0f;
	mainCamera.projection = CAMERA_PERSPECTIVE;

	// grid settings
	float gridSize = 2.0f;

	// input handler
	InputHandler input = InputHandler();

	// level settings
	int movesRemaining = 4;

	// setup story manager
	StoryManager storyManager = StoryManager(originPoint, movesRemaining);
	Level level = Level(gridSize);

	// game loop
	while (!WindowShouldClose()) // run the loop untill the user presses ESCAPE or presses the Close button on the window
	{
		//	-	-	-	-	-	-	-	-	UPDATE	-	-	-	-	-	-	-	-
		storyManager.update(&input);

		// drawing
		BeginDrawing();

		// Setup the back buffer for drawing (clear color and depth buffers)
		ClearBackground(DARKGREEN);

		BeginMode3D(mainCamera);
		storyManager.draw(gridSize);
		level.draw(gridSize);
		EndMode3D();

		// draw some text using the default font
		DrawFPS(20, 40);
		draw_input_controls();
		draw_story_manager_data(&storyManager);

		// end the frame and get ready for the next one  (display frame, poll input, etc...)
		EndDrawing();
	}

	// destroy the window and cleanup the OpenGL context
	CloseWindow();
	return 0;
}
