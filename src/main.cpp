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

#include "resource_dir.h" // utility header for SearchAndSetResourceDir

#define CLOSENESS 0.001f
#define SPEED 0.4f

int main()
{
	// Tell the window to use vsync and work on high DPI displays
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	// Create the window and OpenGL context
	InitWindow(1280, 800, "Hello Raylib");

	// Utility function from resource_dir.h to find the resources folder and set it as the current working directory so we can load from it
	SearchAndSetResourceDir("resources");

	// setup text
	char moveText[20];

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

	// create a character
	Character character = {0};
	character.isMoving = false;
	character.currentPosition = originPoint;
	character.targetPosition = originPoint;
	character.movesRemaining = 18;

	// input handler
	InputHandler inputs = InputHandler();

	// game loop
	while (!WindowShouldClose()) // run the loop untill the user presses ESCAPE or presses the Close button on the window
	{
		//	-	-	-	-	-	-	-	-	UPDATE	-	-	-	-	-	-	-	-
		if (character.isMoving)
		{
			character.currentPosition = Vector3Lerp(
					character.currentPosition,
					character.targetPosition,
					SPEED);

			float distance = Vector3Distance(character.currentPosition, character.targetPosition);
			if (distance < CLOSENESS)
			{
				character.currentPosition = character.targetPosition;
				character.isMoving = false;
			}
		}
		else if (character.movesRemaining > 0)
		{
			Command *command = inputs.handleInput();
			if (command)
			{
				command->execute(&character);
				character.isMoving = true;
				character.movesRemaining--;
			}
		}

		// drawing
		BeginDrawing();

		// Setup the back buffer for drawing (clear color and depth buffers)
		ClearBackground(DARKGREEN);

		BeginMode3D(mainCamera);

		DrawCube(character.currentPosition, gridSize, gridSize, gridSize, PURPLE);

		DrawGrid(10, 1.0f);

		EndMode3D();

		// draw some text using the default font
		DrawFPS(20, 10);
		sprintf(moveText, "Moves Remaining: %d", character.movesRemaining);
		DrawText(moveText, 20, 40, 20, WHITE);

		// end the frame and get ready for the next one  (display frame, poll input, etc...)
		EndDrawing();
	}

	// destroy the window and cleanup the OpenGL context
	CloseWindow();
	return 0;
}
