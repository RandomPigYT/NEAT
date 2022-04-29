#ifndef NEAT_H
#define NEAT_H

#include <stddef.h>
#include <stdint.h>
#include <pthread.h>

typedef struct node_t Node;
typedef struct connection_t Connection;
typedef struct genome_t Genome;

pthread_t draw(void* args);

void createPopulation(uint32_t numberOfInputs, uint32_t numberOfOutputs, uint32_t populationSize);
#endif