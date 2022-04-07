#include "includes/NEAT.h"
#include "includes/NEAT_core.h"
#include <stdio.h>
#include <stdlib.h>
    
uint32_t numSortedNodes = 0;

 

void sortToLayers(Genome* genome){

    Node* sorted = malloc((genome->numberOfNodes - numOutputs) * sizeof(Node));
    
    
    for(uint32_t i = 0; i < numInputs; i++){
        sorted[i] = genome->nodes[i];
        numSortedNodes++;

    }

    while(numSortedNodes != (genome->numberOfNodes - numOutputs)){
        
        
    }

    free(sorted);
}

BOOL contains(uint32_t nodeIndex, Node* sorted){

    BOOL temp = false;
    for(int i = 0; i < numSortedNodes; i++){
        if(sorted[i].index == nodeIndex){
            temp = true;
        }
    }

    return temp;
}

