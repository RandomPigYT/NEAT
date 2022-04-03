CC = gcc
FLAGS = -g -Wall -Wextra -O2 

OBJECT_FILES = createPopulation.o main.o mutate.o genes.o

all: compile link clean

compile: src/createPopulation.c
	$(CC) $(FLAGS) -c src/createPopulation.c
	$(CC) $(FLAGS) -c src/main.c
	$(CC) $(FLAGS) -c src/mutate.c
	$(CC) $(FLAGS) -c src/genes.c

link: createPopulation.o main.o genes.o
	gcc $(OBJECT_FILES) -o build/NEAT.out

clean:
	rm *.o

run:
	clear
	./build/NEAT.out

