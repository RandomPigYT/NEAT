CC = gcc
FLAGS = -g -Wall -Wextra -O2 

OBJECT_FILES = createPopulation.o main.o mutate.o

all: compile link clean

compile: src/createPopulation.c
	$(CC) $(FLAGS) -c src/createPopulation.c
	$(CC) $(FLAGS) -c src/main.c
	$(CC) $(FLAGS) -c src/mutate.c

link: createPopulation.o main.o
	gcc $(OBJECT_FILES) -o build/NEAT.out

clean:
	rm *.o

run:
	clear
	./build/NEAT.out

