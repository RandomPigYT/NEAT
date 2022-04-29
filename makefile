CC = gcc
FLAGS = -g -Wall -Wextra -O2 

OBJECT_FILES = createPopulation.o main.o genes.o layer.o mutate.o draw.o render.o io.o

COMMANDS =compile link clean

LIBS = -lpthread -lSDL2main -lSDL2 -lSDL2_image -lSDL2_gfx -lm


all: $(COMMANDS)

compile: $(SRC)
	$(CC) $(FLAGS) -c src/createPopulation.c
	$(CC) $(FLAGS) -c src/main.c
	$(CC) $(FLAGS) -c src/mutate.c
	$(CC) $(FLAGS) -c src/genes.c
	$(CC) $(FLAGS) -c src/layer.c
	$(CC) $(FLAGS) -c src/draw/draw.c
	$(CC) $(FLAGS) -c src/draw/render.c
	$(CC) $(FLAGS) -c src/draw/io.c

link: $(OBJECT_FILES)
	gcc $(FLAGS)  $(OBJECT_FILES) -o build/NEAT.out $(LIBS)

clean:
	rm *.o

run:
	clear
	./build/NEAT.out

debug:
	gdb build/NEAT.out