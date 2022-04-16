#ifndef NEAT_CORE_H
#define NEAT_CORE_H


#include "NEAT.h"
#include <stdbool.h>


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

    float x, y;

} Node;



typedef struct connection_t{
    float weight;

    uint32_t from;    //outNode
    uint32_t to;   //inNode
    
    uint32_t innovation;

    BOOL isEnabled;

    uint8_t type;

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



Node createNode(uint32_t index);
Connection createConnection(uint32_t to, uint32_t from, uint8_t type);

// Sets the innovation
void setInnovation(Connection* con);

void sortToLayers(Genome* genome);

Genome createGenome();

void mutateConnection(Genome* genome);
void mutateNode(Genome* genome);
#endif

