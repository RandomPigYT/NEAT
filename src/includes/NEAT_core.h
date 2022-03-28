#ifndef NEAT_CORE_H
#define NEAT_CORE_H

#include "NEAT.h"

typedef uint8_t bool;

typedef struct node_t{
    uint32_t index;

    float activation;
    uint32_t layer;

    uint32_t* outNodes;
    uint32_t* inNodes;
} Node;

typedef struct connection_t{
    int32_t weight;

    uint32_t inNode;
    uint32_t outNode;
    
    uint32_t innovation;

    bool isEnabled;

} Connection;


typedef struct genome_t{
    Node* nodes;
    Connection* connections;

    uint32_t numberOfNodes;
    uint32_t numberOfConnections;    
} Genome;


Genome* population;

uint32_t globalInnovation;

uint32_t numInputs;
uint32_t numOutputs;


#endif