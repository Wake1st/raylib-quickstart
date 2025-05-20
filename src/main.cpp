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

inline const char *const BoolToString(bool b)
{
	return b ? "true" : "false";
}

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
	char debugText[64];

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
	Character character(originPoint, 32);

	// input handler
	InputHandler inputs = InputHandler();

	// command storage
	Command *commands[COMMAND_COUNT];
	int cmdIndex = 0;
	int cmdEndex = 0;

	// game loop
	while (!WindowShouldClose()) // run the loop untill the user presses ESCAPE or presses the Close button on the window
	{
		//	-	-	-	-	-	-	-	-	UPDATE	-	-	-	-	-	-	-	-
		if (character.isMoving)
		{
			character.move();
		}
		else if (character.movesRemaining > 0)
		{
			Command *command = inputs.handleInput();
			if (command)
			{
				command->execute(&character);

				commands[cmdIndex++] = command;
				if (cmdIndex > cmdEndex)
				{
					// ensure we know how high the commands go
					cmdEndex = cmdIndex;
				}
				else if (cmdIndex < cmdEndex)
				{
					// we must remove all higher up commands
					for (int i = cmdIndex; i < cmdEndex; i++)
					{
						commands[i] = nullptr;
					}
				}
			}

			//	check for undo and redo
			if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyDown(KEY_Z) && cmdIndex > 0)
			{
				Command *undoCommand = commands[--cmdIndex];
				if (undoCommand)
				{
					undoCommand->undo(&character);
				}
			}
			else if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyDown(KEY_Y) && cmdIndex < cmdEndex)
			{
				Command *redoCommand = commands[cmdIndex++];
				if (redoCommand)
				{
					redoCommand->execute(&character);
				}
			}
		}

		// drawing
		BeginDrawing();

		// Setup the back buffer for drawing (clear color and depth buffers)
		ClearBackground(DARKGREEN);

		BeginMode3D(mainCamera);
		DrawCube(character.getPosition(), gridSize, gridSize, gridSize, PURPLE);
		DrawGrid(10, 1.0f);
		EndMode3D();

		// draw some text using the default font
		sprintf(debugText, "ctrl: %s\tz: %s\ty: %s",
						BoolToString(IsKeyDown(KEY_LEFT_CONTROL)),
						BoolToString(IsKeyDown(KEY_Z)),
						BoolToString(IsKeyDown(KEY_Y)));
		DrawText(debugText, 20, 20, 20, LIGHTGRAY);

		DrawFPS(20, 40);
		sprintf(moveText, "Moves Remaining: %d", character.movesRemaining);
		DrawText(moveText, 20, 60, 20, WHITE);

		// end the frame and get ready for the next one  (display frame, poll input, etc...)
		EndDrawing();
	}

	// destroy the window and cleanup the OpenGL context
	CloseWindow();
	return 0;
}
