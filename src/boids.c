#include "stdlib.h"
#include "math.h"
#include "boids.h"

Boid* newBoid(Vector2 origin, Boid* other) {
     Vector2* positions = malloc(sizeof(Vector2)*3);

     positions[0] = (Vector2){0.0f, -5.0f};
     positions[1] = (Vector2){-5, 5};
     positions[2] = (Vector2){5, 5};

     Boid* boid = malloc(sizeof(Boid));

     int* flockSize;
     Boid** flock;

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

     *boid = (Boid){origin, 0, positions, flock, flockSize};

     return boid;
}

float distance(Vector2 v1, Vector2 v2) {
     Vector2 delta = {fabsf(v1.x - v2.x), fabsf(v1.x - v2.x)};
     return sqrtf(delta.x*delta.x+delta.y*delta.y);
}

Boid** localBoids(Boid* boid) {
     static Boid* localFlock[128];
     int localFlockSize = 0;

     for (int i = 0; i < *boid->flockSize; i++) {
          float dist = distance(boid->flock[i]->origin, boid->origin);
          if (dist > 2 && dist < 40) {
               localFlock[localFlockSize] = boid->flock[i];
               localFlockSize++;
          }
     }

     return localFlock;
}

void rotateBoid(Boid* boid) {
     for (int i = 0; i < 3; i++) {
          float x = boid->positions[i].x;
          float y = boid->positions[i].y;
          boid->positions[i].x = cos(boid->theta) * x - sin(boid->theta) * y;
          boid->positions[i].y = sin(boid->theta) * x + cos(boid->theta) * y;
     }
}

void drawBoid(Boid* boid) {
     Vector2 screenPositions[3] = {boid->positions[0], boid->positions[1], boid->positions[2]};

     for (int i = 0; i < 3; i++) {
          screenPositions[i] = (Vector2){screenPositions[i].x+boid->origin.x, screenPositions[i].y+boid->origin.y};
     }

     DrawTriangle(screenPositions[0], screenPositions[1], screenPositions[2], BLUE);
}
