#pragma once

#ifndef NEAT_CORE_H
#define NEAT_CORE_H


#include "NEAT.h"
#include <stdbool.h>


#define WIDTH_START_COORD 78
#define WIDTH_END_COORD 550
#define HEIGHT_START_COORDS 63
#define HEIGHT_END_COORDS 442


//=========================================================================================================================

// Typedefs

//=========================================================================================================================



typedef uint8_t BOOL;


//=========================================================================================================================

// Struct defenitions

//=========================================================================================================================


typedef struct node_t{
    uint32_t index;

    float activation;
    uint32_t layer;

    
    uint32_t* inNodes;

    uint32_t numInNodes;
    uint32_t remainingInNodeMem;    

    uint8_t type;

    float pos[2];

} Node;



typedef struct connection_t{
    float weight;

    uint32_t from;    
    uint32_t to;   
    
    uint32_t innovation;

    BOOL isEnabled;

    uint8_t type;

    float pos[4];

} Connection;



typedef struct layer_t{

    Node** nodes;
    
    uint32_t numberOfNodes; 
    
} Layer;



typedef struct genome_t{
    Node* nodes;
    Connection* connections;

    uint32_t numberOfNodes;
    uint32_t numberOfConnections;

    uint32_t remainingConMem;
    uint32_t remainingNodeMem;

    Layer* layers;
    
    uint32_t numberOfLayers;

    float fitness;
    float adjustedFitness;

} Genome;


typedef struct memory_t{

    uint32_t in;
    uint32_t out;

    uint32_t innovation;
} Memory;


//=========================================================================================================================

// Enums

//=========================================================================================================================


enum node_types{
    INPUT,
    OUTPUT,
    HIDDEN,
    BIAS
};



enum connection_types{
    FEED_FORWARD,
    RECURRENT
};


//=========================================================================================================================

// Global variables

//=========================================================================================================================

Genome* population;
uint32_t popSize;



uint32_t globalInnovationNumber;

Memory* geneMemory;
uint32_t numGenesInMemory;
uint32_t remainingMemory;   // To keep track of the amount of malloc'd memory remaining 




uint32_t numInputs;
uint32_t numOutputs;



//=========================================================================================================================

// Fucntions

//=========================================================================================================================

void mutate(Genome* genome);

BOOL isPaused;


Node createNode(uint32_t index);
Connection createConnection(uint32_t to, uint32_t from, uint8_t type);

// Sets the innovation
void setInnovation(Connection* con);

void sortToLayers(Genome* genome);

Genome createGenome();

void mutateConnection(Genome* genome);
void mutateNode(Genome* genome);

void removeCon(Genome* genome, uint32_t innovation);
void removeNodeMut(Genome* genome);

Node getNode(uint32_t index, Genome* genome);
#endif

