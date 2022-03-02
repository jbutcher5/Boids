CC = clang
CFLAGS = -lraylib -lm -o boids
source := $(wildcard src/*.c)

compile:
	$(CC) $(source) $(CFLAGS) -g3

optimised:
	$(CC) $(source) $(CFLAGS) -O3

run: optimised
	./boids

debug: compile
	/bin/gdb boids

test: compile
	./boids

clean:
	rm -f boids
