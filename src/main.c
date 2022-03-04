#include "raylib.h"
#include "rlgl.h"
#include "boids.h"
#include "stdlib.h"

#define FPS 60
#define WIDTH 800
#define HEIGHT 450
#define TITLE "Boids Example"

int main(void) {
	InitWindow(WIDTH, HEIGHT, TITLE);
	rlDisableBackfaceCulling();
	SetTargetFPS(FPS);

	Boid* flock[256];

	for (int i = 0; i < 256; i++)
		flock[i] = newBoid((Vector2){GetRandomValue(0, WIDTH), GetRandomValue(i, HEIGHT)}, (Vector2){20, 20}, 0, 6);

	while (!WindowShouldClose()){
		for (int i = 0; i < 256; i++)
			updateBoid(flock[i], flock, 256);

		BeginDrawing();
		ClearBackground(RAYWHITE);

		for (int i = 0; i < 256; i++)
			drawBoid(flock[i]);

		EndDrawing();
	}

	CloseWindow();

	return 0;
}
