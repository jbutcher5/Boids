#!/bin/sh

echo "INFO: Deleting existing build"
rm -rf ./build/
echo "INFO: Copying src to build"
cp -r ./src ./build
echo "INFO: Compiling source code"
clang ./build/*.c -lraylib -o ./boids
