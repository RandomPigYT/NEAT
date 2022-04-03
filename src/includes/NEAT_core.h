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

    uint32_t* outNodes;
    uint32_t* inNodes;

    uint32_t numInNodes;
    uint32_t numOutNodes;

    

    uint8_t type;

} Node;



typedef struct connection_t{
    float weight;

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

    Layer* layers;
    
    uint32_t numberOfLayers;

} Genome;



typedef struct layer_t{

    Node** nodes;
    
    uint32_t numberOfNodes; 
    
} Layer;

//=========================================================================================================================

// Enums

//=========================================================================================================================


enum node_types{
    INPUT,
    OUTPUT,
    HIDDEN
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
    
Connection* geneMemory;
uint32_t geneMemorySize;



uint32_t numInputs;
uint32_t numOutputs;

//=========================================================================================================================

// Fucntions

//=========================================================================================================================

void mutate(Genome* genome);



Node createNode(uint32_t index, uint8_t type);
Connection createConnection(uint32_t inNode, uint32_t outNode, uint32_t innovation, uint8_t type);


#endif

