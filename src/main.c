#include "raylib.h"
#include "rlgl.h"
#include "stdlib.h"
#include "stdio.h"
#include "math.h"

#define FPS 60
#define WIDTH 800
#define HEIGHT 450
#define TITLE "Boids Example"

typedef struct Boid {
	Vector2 origin;
	Vector2* positions;
	struct Boid** flock;
	int* flockSize;
} Boid;

Boid* newBoid(Vector2 origin, Boid* other) {
	Vector2* positions = malloc(sizeof(Vector2)*3);

	positions[0] = (Vector2){0.0f, -5.0f};
	positions[1] = (Vector2){-5, 5};
	positions[2] = (Vector2){5, 5};

	Boid* boid = malloc(sizeof(Boid));

	int* flockSize;
	struct Boid** flock;

	if (other == NULL){
		flockSize = malloc(sizeof(int));
		flock = malloc(sizeof(Boid*)*4);

		flock[0] = boid;
		*flockSize = 1;
	} else {
		flockSize = other->flockSize;
		flock = other->flock;

		other->flock[*other->flockSize] = boid;
		*other->flockSize += 1;
	}

	*boid = (Boid){origin, positions, flock, flockSize};

	return boid;
}

void rotateBoid(Boid* boid, float th) {
	for (int i = 0; i < 3; i++) {
		float x = boid->positions[i].x;
		float y = boid->positions[i].y;
		boid->positions[i].x = cos(th) * x - sin(th) * y;
		boid->positions[i].y = sin(th) * x + cos(th) * y;
	}
}

void drawBoid(Boid* boid) {
	Vector2 screenPositions[3] = {boid->positions[0], boid->positions[1], boid->positions[2]};

	for (int i = 0; i < 3; i++) {
		screenPositions[i] = (Vector2){screenPositions[i].x+boid->origin.x, screenPositions[i].y+boid->origin.y};
	}

	DrawTriangle(screenPositions[0], screenPositions[1], screenPositions[2], BLUE);
}

int main(void) {
	InitWindow(WIDTH, HEIGHT, TITLE);
	rlDisableBackfaceCulling();
	SetTargetFPS(FPS);

	Boid* first = newBoid((Vector2){200, 200}, NULL);
	Boid* second = newBoid((Vector2){230, 200}, first);
	rotateBoid(second->flock[0], 1.5f);

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
