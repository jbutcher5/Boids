CC = clang
CFLAGS = -lraylib -lm -o boids
source := $(wildcard src/*.c)

build:
	$(CC) $(source) $(CFLAGS) -g3

build_debug:
	$(CC) $(source) $(CFLAGS) -g3 -fsanitize=address -O1 -fno-omit-frame-pointer -fno-optimize-sibling-calls

build_release:
	$(CC) $(source) $(CFLAGS) -g3

gdb: build_debug
	/bin/gdb boids

debug: build_debug
	./boids

run: build
	./boids

clean:
	rm -f boids
