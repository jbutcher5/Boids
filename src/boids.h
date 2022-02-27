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
float getTheta(Vector2 v1, Vector2 v2);
void applyCohesion(Boid* boid);
void rotateBoid(Boid* boid, float theta);
void drawBoid(Boid* boid);
