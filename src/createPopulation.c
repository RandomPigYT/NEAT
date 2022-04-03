#include "includes/NEAT.h"
#include "includes/NEAT_core.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

Node createNode(uint32_t index, uint8_t type){
    Node node;
    
    node.activation = 0.0f;
    
    
    node.layer = 0;

    node.numInNodes = 0;
    node.numOutNodes = 0;

    node.numOutRecurrent = 0;
    node.numInRecurrent = 0;
    
    node.type = type;

    node.index = index;

    if(type == INPUT){
        node.layer = 0;
    }

    else{
        node.layer = 1;
    }
    return node;
}


Genome createGenome(){

    Genome genome;

    uint32_t numberOfNodes = numInputs + numOutputs;
    genome.nodes = malloc(numberOfNodes * sizeof(Node));

    //assert(genome.nodes != NULL && "Failed to allocate memory to genome.nodes\n");

    if(genome.nodes == NULL){
        fprintf(stderr, "Failed to allocate memory to genome.nodes\n");

        exit(EXIT_FAILURE);
    }
    genome.numberOfNodes = numInputs + numOutputs;
 
    for(uint32_t i = 0; i < numInputs; i++){
        genome.nodes[i] = createNode(i, INPUT);
    }

    for(uint32_t i = numInputs; i < (numInputs + numOutputs); i++){
        genome.nodes[i] = createNode(i, OUTPUT);
    }

    genome.numberOfLayers = 2;

    return genome;
}

void createPopulation(uint32_t numberOfInputs, uint32_t numberOfOutputs, uint32_t populationSize){
    numInputs = numberOfInputs;
    numOutputs = numberOfOutputs;

    population = malloc(populationSize * sizeof(Genome));

    for(uint32_t i = 0; i < populationSize; i++){
        population[i] = createGenome();
    }
    return;
}


