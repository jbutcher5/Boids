#include "raylib.h"

int main(void)
{
	const int width = 800;
	const int height = 450;

	InitWindow(width, height, "Boids");
	
	SetTargetFPS(60);

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(RAYWHITE);
		DrawText("test", 190, 200, 20, LIGHTGRAY);
		EndDrawing();
	}

	CloseWindow();

	return 0;
}
