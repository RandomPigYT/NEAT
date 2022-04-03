#ifndef NEAT_CORE_H
#define NEAT_CORE_H

#include "NEAT.h"

typedef uint8_t BOOL;

typedef struct node_t{
    uint32_t index;

    float activation;
    uint32_t layer;

    uint32_t* outNodes;
    uint32_t* inNodes;

    uint32_t numInNodes;
    uint32_t numOutNodes;

    uint32_t numInRecurrent;
    uint32_t numOutRecurrent;

    uint8_t type;

} Node;

typedef struct connection_t{
    int32_t weight;

    uint32_t inNode;
    uint32_t outNode;
    
    uint32_t innovation;

    BOOL isEnabled;

    uint8_t type;

} Connection;


typedef struct genome_t{
    Node* nodes;
    Connection* connections;

    uint32_t numberOfNodes;
    uint32_t numberOfConnections;

    uint32_t numberOfLayers;

    Genome** layers;
} Genome;

enum node_types{
    INPUT,
    OUTPUT,
    HIDDEN
};

enum connection_types{
    FEED_FORWARD,
    RECURRENT
};

Genome* population;

uint32_t globalInnovation;

uint32_t numInputs;
uint32_t numOutputs;

uint32_t popSize;


#endif

