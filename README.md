# Boids

A basic simulation of boids in the C programming language using [raylib](https://www.raylib.com/) for rendering.

## What are Boids?

Put simply, [boids](https://en.wikipedia.org/wiki/Boids) are flocking simulations. They emulate the movement of fish shoals or bird flocks which are all forms of [swarm intelligence](https://en.wikipedia.org/wiki/Swarm_intelligence). Each object (I shall be referring to them singularly as a 'boid') has a set of rules (cohesion, separation and alignment) which can not been seen individually however when in a group of other boids a flock beings to appear, this is a demonstration of [emergence](https://en.wikipedia.org/wiki/Emergence).

## Why did I choose C?

You may be currious why I chose [the C programming language](https://en.wikipedia.org/wiki/C_(programming_language)), instead of a more recent and safer language like [Rust](https://www.rust-lang.org/) or [Python](https://www.python.org/). This is because I see C as an industry standard despite all of the flaws it may have and I accessible to many programmers of all backgrounds.

## Under the Hood

In-depth explanations of boid implementations specifically in C.

### Boid Functions

This section will be dealing with the functions defined in [src/boids.h](https://github.com/KJ002/Boids/blob/main/src/boids.h) and/or implemented in [src/boids.c](https://github.com/KJ002/Boids/blob/main/src/boids.c).

Function | Explantion
---|---
`newBoid` | Takes `Boid` construction parameters and applies the rotational transformation to the `Boid::positions` as specified by the `rotation` parameter around the `origin` parameter.
`updateBoid` | The most complex function of all of them. Increments the origin per the boid velocity and the change in time (seconds). Aggregates pointers to local boids and passes these to `cohesion`, `separation` and `alignment` for that boid. Then rotate the boid based on the decided rotation and update it `lastUpdate`.
`rotateBoid` | Applies a rotation of `theta` radians to the boid. It does this through [rotational matrices](https://en.wikipedia.org/wiki/Rotation_matrix).
`drawBoid` | A function specifically designed to link the goings on of the boids and render them to the screen using raylib.
`distance` | A basic [Pythagorean theorem](https://en.wikipedia.org/wiki/Pythagorean_theorem) function for two vectors calculating the distance between two points.
`getLocalFlock` | Gets all the boids within a 50px radius of the boid.
`getRotation` | Gets the bearing of two points relative to `v1` regardless of quadrant using [`atan2`](https://en.wikipedia.org/wiki/Atan2).
`getCohesion` | Mean all the origins of boids within the `localFlock` parameter
`getAlignment` | Get the mean alignment of all of the boids within `localFlock`
`getSeparation` | Gets the "inverse" rotation (opposite direction) of the nearest boid.
