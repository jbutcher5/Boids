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

	first->velocity = (Vector2){20, 20};
	second->velocity = (Vector2){20, 20};

	while (!WindowShouldClose()){

		if (IsKeyDown(KEY_RIGHT)) second->origin.x += 2.0f;
        if (IsKeyDown(KEY_LEFT)) second->origin.x -= 2.0f;
        if (IsKeyDown(KEY_UP)) second->origin.y -= 2.0f;
        if (IsKeyDown(KEY_DOWN)) second->origin.y += 2.0f;

		updateBoid(first);
		updateBoid(second);

		BeginDrawing();
		ClearBackground(RAYWHITE);
		drawBoid(first);
		drawBoid(second);
		EndDrawing();
	}

	CloseWindow();

	return 0;
}
