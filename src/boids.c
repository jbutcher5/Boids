#include "stdlib.h"
#include "math.h"
#include "boids.h"
#include <math.h>
#include <raylib.h>

struct LocalFlock {
     Boid flock[32];
     int size;
} typedef LocalFlock;

Boid* newBoid(Vector2 origin, Vector2 velocity) {
     Vector2* positions = malloc(sizeof(Vector2)*3);

     positions[0] = (Vector2){0.0f, -5.0f};
     positions[1] = (Vector2){-5, 5};
     positions[2] = (Vector2){5, 5};

     Boid* boid = malloc(sizeof(Boid));
     *boid = (Boid){origin, 0, positions, velocity, GetTime()};

     return boid;
}

float distance(Vector2 v1, Vector2 v2) {
     Vector2 delta = {fabsf(v1.x - v2.x), fabsf(v1.y - v2.y)};
     return sqrtf(delta.x*delta.x+delta.y*delta.y);
}

LocalFlock getLocalFlock(Boid* boid, Boid** flock, int flockSize) {
     LocalFlock localFlock;
     localFlock.size = 0;

     for (int i = 0; i < flockSize; i++) {
          float dist = distance(flock[i]->origin, boid->origin);
          if (flock[i] != boid && dist < 60) {
               localFlock.flock[localFlock.size] = *flock[i];
               localFlock.size += 1;
          }
          i++;
     }

     return localFlock;
}

float getRotation(Vector2 v1, Vector2 v2) {
     Vector2 delta = {v1.x - v2.x, v1.y - v2.y};

     return atan2f(-delta.x, delta.y);
}

float getCohesion(Boid* boid, LocalFlock localFlock) {
     Vector2 mean = {0, 0};

     for (int i = 0; i < localFlock.size; i++) {
          mean.x += localFlock.flock[i].origin.x;
          mean.y += localFlock.flock[i].origin.y;
     }

     mean = (Vector2){mean.x/localFlock.size, mean.y/localFlock.size};
     return getRotation(boid->origin, mean);
}

float getAlignment(Boid* boid, LocalFlock localFlock) {
     float meanRotation = 0;

     for (int i = 0; i < localFlock.size; i++)
          meanRotation += localFlock.flock[i].rotation;
     meanRotation /= localFlock.size;

     return meanRotation;
}

float getSeparation(Boid* boid, LocalFlock localFlock) {
     float meanRotation = 0;

     for (int i = 0; i < localFlock.size; i++)
          meanRotation += getRotation(boid->origin, localFlock.flock[i].origin);
     meanRotation /= localFlock.size;

     return 2*M_PI-meanRotation;
}

void updateBoid(Boid* boid, Boid** flock, int flockSize) {
     double now = GetTime();
     double deltaTime = now - boid->lastUpdate;

     LocalFlock localFlock = getLocalFlock(boid, flock, flockSize);

     float rules[] = {getCohesion(boid, localFlock), getAlignment(boid, localFlock), getSeparation(boid, localFlock)};

     float meanRule = 0;
     for (int i = 0; i < 3; i++)
          meanRule += rules[i];
     meanRule /= 3;

     rotateBoid(boid, meanRule);

     Vector2 velocity = {sinf(boid->rotation)*boid->velocity.x, -cosf(boid->rotation)*boid->velocity.y};
     boid->lastUpdate = now;

     boid->origin = (Vector2){boid->origin.x + velocity.x * deltaTime, boid->origin.y + velocity.y * deltaTime};
     boid->origin = (Vector2){fmod(boid->origin.x+800, 800), fmod(boid->origin.y+450, 450)};
}

void rotateBoid(Boid* boid, float theta) {
     float rotationDelta = theta - boid->rotation;

     for (int i = 0; i < 3; i++) {
          float x = boid->positions[i].x;
          float y = boid->positions[i].y;
          boid->positions[i].x = cos(rotationDelta) * x - sin(rotationDelta) * y;
          boid->positions[i].y = sin(rotationDelta) * x + cos(rotationDelta) * y;
     }

     boid->rotation += rotationDelta;
}

void drawBoid(Boid* boid) {
     Vector2 screenPositions[3] = {boid->positions[0], boid->positions[1], boid->positions[2]};

     for (int i = 0; i < 3; i++) {
          screenPositions[i] = (Vector2){screenPositions[i].x+boid->origin.x, screenPositions[i].y+boid->origin.y};
     }

     DrawTriangle(screenPositions[0], screenPositions[1], screenPositions[2], BLUE);
}
