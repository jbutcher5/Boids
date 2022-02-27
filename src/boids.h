#pragma once
#include "raylib.h"

typedef struct Boid {
    Vector2 origin;
    float theta;
    Vector2* positions;
    struct Boid** flock;
    int* flockSize;
    Vector2 velocity;
    double lastUpdate;
} Boid;

Boid* newBoid(Vector2 origin, Boid* other);
void updateBoid(Boid* boid);
void rotateBoid(Boid* boid, float theta);
void drawBoid(Boid* boid);
