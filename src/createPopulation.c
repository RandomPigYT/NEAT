#include "includes/NEAT.h"
#include "includes/NEAT_core.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


Node addNode(uint32_t index, uint8_t type, Genome* genome){
    Node node;
    
    node.activation = 0.0f;
      
      
    node.numInNodes = 0;
    
    

       
    node.type = type;

    node.index = index;

    if(type == INPUT || type == BIAS){
        node.layer = 0;
    }

    else if(type == OUTPUT){
        node.layer = 1;
    }

    genome->remainingNodeMem--;

    return node;
}



Genome createGenome(){

    Genome genome;

    uint32_t numberOfNodes = numInputs + numOutputs;
    genome.nodes = malloc((numberOfNodes + 10) * sizeof(Node));

    genome.remainingNodeMem = numberOfNodes + 10;

    genome.numberOfConnections = 0;

    //assert(genome.nodes != NULL && "Failed to allocate memory to genome.nodes\n");

    if(genome.nodes == NULL){
        fprintf(stderr, "Failed to allocate memory to genome.nodes\n");

        exit(EXIT_FAILURE);
    }
    genome.numberOfNodes = numInputs + numOutputs;
    
    genome.nodes[0] = addNode(0, BIAS, &genome); // Create the bias neuron

    for(uint32_t i = 1; i < numInputs; i++){
        genome.nodes[i] = addNode(i, INPUT, &genome);
    }

    for(uint32_t i = numInputs; i < (numInputs + numOutputs); i++){
        genome.nodes[i] = addNode(i, OUTPUT, &genome);
    }

    genome.numberOfLayers = 2;  // Since only the input and the output layers exist at this stage

  
    return genome;

    
}

void createPopulation(uint32_t numberOfInputs, uint32_t numberOfOutputs, uint32_t populationSize){
    
    
    
    numInputs = numberOfInputs + 1;
    numOutputs = numberOfOutputs;

    population = malloc(populationSize * sizeof(Genome));

    for(uint32_t i = 0; i < populationSize; i++){
        population[i] = createGenome();
    }
    return;
}


