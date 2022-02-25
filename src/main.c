#include "raylib.h"
#define FPS 60
#define WIDTH 800
#define HEIGHT 450
#define TITLE "Boids Example"

int main(void){
	InitWindow(WIDTH, HEIGHT, TITLE);
	SetTargetFPS(FPS);

	while (!WindowShouldClose()){
		BeginDrawing();
		ClearBackground(RAYWHITE);
		DrawText("test", 190, 200, 20, LIGHTGRAY);
		EndDrawing();
	}

	CloseWindow();

	return 0;
}
