CC = gcc
FLAGS = -g -Wall -Wextra -std=c17 -O2

OBJECT_FILES = $(wildcard obj/*.o)# obj/createPopulation.o obj/main.o obj/genes.o obj/layer.o obj/mutate.o obj/draw.o obj/render.o obj/io.o obj/circle.o obj/crossover.o

COMMANDS =compile link

LIBS = -lpthread -lSDL2main -lSDL2 -lSDL2_image -lSDL2_gfx -lm


all: $(COMMANDS)

compile: 
	$(CC) $(FLAGS) -c src/createPopulation.c
	$(CC) $(FLAGS) -c src/main.c
	$(CC) $(FLAGS) -c src/mutate.c
	$(CC) $(FLAGS) -c src/genes.c
	$(CC) $(FLAGS) -c src/layer.c
	$(CC) $(FLAGS) -c src/draw/draw.c
	$(CC) $(FLAGS) -c src/draw/render.c
	$(CC) $(FLAGS) -c src/draw/io.c
	$(CC) $(FLAGS) -c src/draw/circle.c
	$(CC) $(FLAGS) -c src/crossover.c
	$(CC) $(FLAGS) -c src/util/sort.c
	$(CC) $(FLAGS) -c src/util/decls.c
	mv *.o obj

link: $(OBJECT_FILES)
	gcc $(FLAGS) $(OBJECT_FILES) -o bin/NEAT.out $(LIBS)

clean:
	rm obj/*
	rm bin/*
run:
	clear
	./bin/NEAT

debug:
	gdb bin/NEAT.out
