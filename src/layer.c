#include "includes/NEAT.h"
#include "includes/NEAT_core.h"
#include <stdio.h>
#include <stdlib.h>

uint32_t numSortedNodes = 0;

uint32_t* sorted;

BOOL conatins(uint32_t index){

    for(uint32_t i = 0; i < numSortedNodes; i++){
        if(sorted[i] != index) continue;
        else return true;            
    }
    return false;
}

Connection findCon(uint32_t to, uint32_t from, Genome* genome){

    for(uint32_t i = 0; i < genome->numberOfConnections; i++){
        if(genome->connections[i].to == to && genome->connections[i].from == from) return genome->connections[i];
    }
    
}   



void sortToLayers(Genome* genome){
    sorted = malloc(genome->numberOfNodes * sizeof(Node));

    uint32_t maxLayers = 0;
    // Load the input nodes into the buffer to sort
    {
        uint32_t index = 0;
        
        for(uint32_t i = 0; i < genome->numberOfNodes; i++){
            if(genome->nodes[i].type == INPUT || genome->nodes[i].type == BIAS){
                sorted[index] = genome->nodes[i].index;
                numSortedNodes++;
                index++;
            }
        }
    }
    printf("%d\n", numSortedNodes);

    BOOL isSorted = false;

    while (!isSorted){
        
        uint32_t* buffer;

        buffer = malloc(genome->numberOfNodes * sizeof(Node));
        uint32_t buffIndex = 0;
        
        isSorted = true;

        for(uint32_t i = numInputs + numOutputs; i < genome->numberOfNodes; i++){
            BOOL temp = true;
            for(uint32_t j = 0; j < genome->nodes[i].numInNodes; j++){
                
                
                Connection con = findCon(genome->nodes[i].index, genome->nodes[i].inNodes[j], genome);
                
                if(!conatins(genome->nodes[i].inNodes[j]) && con.type != RECURRENT && con.isEnabled)  temp = false; 
            }
        }   

        free(buffer);
    }
    
    
}



