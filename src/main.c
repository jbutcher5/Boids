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

	Boid* first = newBoid((Vector2){200, 200}, NULL);
	Boid* second = newBoid((Vector2){230, 200}, first);
	second->flock[0]->theta = 3.f;
	rotateBoid(second->flock[0]);

	while (!WindowShouldClose()){
		BeginDrawing();
		ClearBackground(RAYWHITE);
		drawBoid(first);
		drawBoid(second);
		EndDrawing();
	}

	CloseWindow();

	return 0;
}
