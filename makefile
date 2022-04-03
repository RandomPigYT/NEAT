CC = gcc
FLAGS = -g -Wall -Wextra -O2 

all: compile link clean

compile: src/createPopulation.c
	$(CC) $(FLAGS) -c src/createPopulation.c
	$(CC) $(FLAGS) -c src/main.c
link: createPopulation.o main.o
	gcc createPopulation.o main.o -o build/NEAT.out
clean:
	rm *.o

run:
	./build/NEAT.out

