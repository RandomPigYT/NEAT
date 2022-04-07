#include "includes/NEAT.h"
#include "includes/NEAT_core.h"
#include <stdio.h>
#include <stdlib.h>

uint32_t numSortedNodes = 0;

 
BOOL contains(uint32_t nodeIndex, uint32_t* sorted){

    BOOL temp = false;
    for(int i = 0; i < numSortedNodes; i++){
        if(sorted[i] == nodeIndex){
            temp = true;
        }
    }

    return temp;
}

Connection findCon(Genome* genome, uint32_t in, uint32_t out){
    for(uint32_t i = 0; i < genome->numberOfConnections; i++){
        if(genome->connections[i].inNode == in && genome->connections[i].outNode == out) return genome->connections[i];
    }
}


void sortToLayers(Genome* genome){

    uint32_t maxLayers = 1;
    uint32_t* sorted = malloc((genome->numberOfNodes - numOutputs) * sizeof(Node));
    
    // Loads input nodes into "sorted" to check against
    for(uint32_t i = 0; i < numInputs; i++){
        sorted[i] = genome->nodes[i].index;
        numSortedNodes++;

    }

    // Does the sorting

    while(numSortedNodes != (genome->numberOfNodes - numOutputs)){

        uint32_t* buffer = malloc(10 * sizeof(uint32_t));
        uint32_t buffMem = 10;

        uint32_t buffSize = 0;
        // Iterates through the nodes
        for(uint32_t i = numInputs + numOutputs; i < genome->numberOfNodes; i++){
            BOOL temp = true;

            // Iterates through the in nodes
            for(uint32_t j = 0; j < genome->nodes[i].numInNodes; j++){
                
                // Recurrent connections aren't counted by the layering function
                if(!contains(genome->nodes[i].inNodes[j], sorted) && findCon(genome, genome->nodes[i].index, genome->nodes[i].inNodes[j]).type != RECURRENT){
                    temp = false;
                    break;
                }
                    
            }

            if(temp){
                
                if(buffMem == 0){
                    buffer = realloc(buffer, (buffSize + 10) * sizeof(uint32_t));
                    buffMem = 10;

                    buffer[buffSize] = genome->nodes[i].index;
                    buffMem--;
                    buffSize++;
                }

                else{
                    buffer[buffSize] = genome->nodes[i].index;
                    buffMem--;
                    buffSize++;
                }
                genome->nodes[i].layer = maxLayers;
            }

            
        }

        
        for(uint32_t i = 0; i < buffSize; i++){
            sorted[numSortedNodes] = buffer[i];
            numSortedNodes++;
        }

        maxLayers++;
        free(buffer);
        printf("Hello\n");
    }

    // Assigns a layer greater than the max layers of the hidden nodes to the output nodes
    for(uint32_t i = numInputs; i < (numInputs + numOutputs); i++){
        genome->nodes[i].layer = maxLayers + 1;
    }

    //// MEMORY LEAK!!!
    free(sorted);

    return;
}



