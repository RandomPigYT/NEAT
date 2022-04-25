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

Node getNode(uint32_t index, Genome* genome){
    for(uint32_t i = 0; i < genome->numberOfNodes; i++){
        if(genome->nodes[i].index == index) return genome->nodes[i];
    }
}

size_t currentSize;

uint32_t recursiveSort(Node node, uint32_t currentLayer, Genome* genome){
    if(node.type == INPUT || node.type == BIAS) return currentLayer;

    

    currentLayer++;
    uint32_t temp = currentLayer;


    for(uint32_t i = 0; i < node.numInNodes; i++){
        
        Connection con = findCon(node.index, node.inNodes[i], genome);

        if(con.type == RECURRENT || con.isEnabled == false){;}

        else{ 
            uint32_t tempIndex = recursiveSort(getNode(node.inNodes[i], genome), temp, genome);

            if(tempIndex >= temp) temp = tempIndex;
        }
    }
    return temp;
}

uint32_t findMaxLayer(Genome* genome){
    uint32_t maxLayer = 0;
    for(uint32_t i = 0; i < genome->numberOfNodes; i++){
        if(genome->nodes[i].layer > maxLayer && genome->nodes[i].type != OUTPUT) maxLayer = genome->nodes[i].layer;
    }

    return maxLayer;
}


void sortToLayers(Genome* genome){
    sorted = malloc(genome->numberOfNodes * sizeof(Node));
    numSortedNodes = 0;

    uint32_t maxLayers = 1;
    // Load the input nodes into the buffer to sort
    
    for(uint32_t i = 0; i < genome->numberOfNodes; i++){
        genome->nodes[i].layer = recursiveSort(genome->nodes[i], 0, genome);
    }

    uint32_t outputLayer = findMaxLayer(genome) + 1;
    
    for(uint32_t i = 0; i < genome->numberOfNodes; i++){
        if(genome->nodes[i].type == OUTPUT) genome->nodes[i].layer = outputLayer;
    }

    // while (!isSorted){
        
    //     uint32_t* buffer;

    //     buffer = malloc(genome->numberOfNodes * sizeof(Node));
    //     uint32_t buffIndex = 0;
        
    //     isSorted = true;
    //     for(uint32_t i = numInputs + numOutputs; i < genome->numberOfNodes; i++){
    //     // Scroll through the nodes


    //         BOOL temp = true;
    //         for(uint32_t j = 0; j < genome->nodes[i].numInNodes; j++){
    //             // Scroll through the inNodes of the current node
                
    //             // Check if the current node's inNodes have been sorted
    //             Connection con = findCon(genome->nodes[i].index, genome->nodes[i].inNodes[j], genome);
                
    //             if(!conatins(genome->nodes[i].inNodes[j]) && con.type != RECURRENT && con.isEnabled)  temp = false; 
    //         }

    //         if(!temp) isSorted = false;

    //         // Add the current node to the buffer
    //         else{
    //             buffer[buffIndex] = genome->nodes[i].index;
    //             genome->nodes[i].layer = maxLayers;
    //             buffIndex++;
    //         }
    //     }   

    //     for( uint32_t i = 0; i < buffIndex; i++){
    //         sorted[numSortedNodes] = buffer[i];
    //         numSortedNodes++;
    //     }
        
    //     maxLayers++;
    //     free(buffer);
    // }
    
    
    // for(uint32_t i = 0; i < genome->numberOfNodes; i++){

    //     if(genome->nodes[i].type == OUTPUT){
    //         genome->nodes[i].layer = maxLayers;
    //     }
    // }

    return;
}



