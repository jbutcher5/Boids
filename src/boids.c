#include "stdlib.h"
#include "math.h"
#include "boids.h"
#include <math.h>

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
     Vector2 delta = {fabsf(v1.x - v2.x), fabsf(v1.y - v2.y)};
     return sqrtf(delta.x*delta.x+delta.y*delta.y);
}

Boid** getLocalFlock(Boid* boid) {
     Boid** localFlock = malloc(sizeof(Boid*)*32);
     int localFlockSize = 0;

     for (int i = 0; i < *boid->flockSize; i++) {
          float dist = distance(boid->flock[i]->origin, boid->origin);
          if (boid->flock[i] != boid && dist < 60) {
               localFlock[localFlockSize] = boid->flock[i];
               localFlockSize++;
          }
     }

     return localFlock;
}

int getLocalFlockSize(Boid** localFlock) {
     int result = 0;
     Boid* currentBoid = *localFlock;

     while (currentBoid) {
          result++;
          currentBoid = localFlock[result];
     }

     return result;
}

float getTheta(Vector2 v1, Vector2 v2) {
     Vector2 delta = {v1.x - v2.x, v1.y - v2.y};

     return atan2f(-delta.x, delta.y);
}

void applyCohesion(Boid* boid) {
     Boid** localFlock = getLocalFlock(boid);
     int localFlockSize = getLocalFlockSize(localFlock);

     Vector2 mean = {0, 0};

     for (int i = 0; i < localFlockSize; i++) {
          mean.x += localFlock[i]->origin.x;
          mean.y += localFlock[i]->origin.y;
     }

     free(localFlock);

     mean = (Vector2){mean.x/localFlockSize, mean.y/localFlockSize};
     rotateBoid(boid, getTheta(boid->origin, mean));
}

void rotateBoid(Boid* boid, float theta) {
     float rotationDelta = theta - boid->theta;

     for (int i = 0; i < 3; i++) {
          float x = boid->positions[i].x;
          float y = boid->positions[i].y;
          boid->positions[i].x = cos(rotationDelta) * x - sin(rotationDelta) * y;
          boid->positions[i].y = sin(rotationDelta) * x + cos(rotationDelta) * y;
     }

     boid->theta += rotationDelta;
}

void drawBoid(Boid* boid) {
     Vector2 screenPositions[3] = {boid->positions[0], boid->positions[1], boid->positions[2]};

     for (int i = 0; i < 3; i++) {
          screenPositions[i] = (Vector2){screenPositions[i].x+boid->origin.x, screenPositions[i].y+boid->origin.y};
     }

     DrawTriangle(screenPositions[0], screenPositions[1], screenPositions[2], BLUE);
}
