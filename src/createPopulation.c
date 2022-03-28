#include "includes/NEAT.h"
#include "includes/NEAT_core.h"
#include <stdio.h>
#include <stdlib.h>

Node createNode(uint32_t index, u_int32_t numberOfInNodes, u_int32_t numberOfOutNodes){
    Node node;
    
    node.activation = 0.0f;
    node.inNodes = malloc(numberOfInNodes * sizeof(uint32_t));
    node.outNodes = malloc(numberOfOutNodes * sizeof(uint32_t));
    node.layer = 0;

    return node;
}

Connection createConnection(){

}

void createPopulation(uint32_t numberOfInputs, uint32_t numberOfOutputs, uint32_t populationSize){
    numInputs = numberOfInputs;
    numOutputs = numberOfOutputs;
    return;
}