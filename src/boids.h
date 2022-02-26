#pragma once
#include "raylib.h"

typedef struct Boid {
    Vector2 origin;
    float theta;
    Vector2* positions;
    struct Boid** flock;
    int* flockSize;
} Boid;

Boid* newBoid(Vector2 origin, Boid* other);
Boid** localBoids(Boid* boid);
void rotateBoid(Boid* boid);
void drawBoid(Boid* boid);
