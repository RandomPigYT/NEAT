#include "includes/NEAT.h"
#include "includes/NEAT_core.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


float connectionMutationProb = 0.8f;
float nodeMutationProbability = 0.2f;

BOOL hasSetSeed = false;

uint32_t* findNode(uint32_t index, Genome genome){


    for(uint32_t i = 0; i < genome.numberOfNodes; i++){
        
        if(genome.nodes[i].index == index){
            
            
            uint32_t temp[2] = {genome.nodes[i].index, true};
            
            return temp;
        }
    }

    uint32_t temp[2] = {NULL, false};
    return temp;
}

void addConnection(Genome* genome){

    BOOL outNodeExists = false;
    BOOL inNodeExists = false;

    while(!outNodeExists && !inNodeExists){

        uint32_t out = ((int) rand() / RAND_MAX) * genome->numberOfNodes;
        uint32_t in = ((int) rand() / RAND_MAX) * genome->numberOfNodes;

        uint32_t* outIndex = findNode(out, *genome);
        uint32_t* inIndex = findNode(in, *genome);
        
        if(!outIndex[1] || !inIndex[1]) continue;   

        if(genome->nodes[outIndex[0]].layer > genome->nodes[inIndex[0]].layer){
            if(genome->nodes[outIndex[0]].numOutNodes == 0){
                genome->nodes[outIndex[0]].outNodes = malloc(sizeof(uint32_t));
            }

            else{
                genome->nodes[outIndex[0]].outNodes = realloc(genome->nodes[outIndex[0]].outNodes, genome->nodes[outIndex[0]].numOutNodes + 1);
            }
        }
    }

}

void mutateNode(Genome* genome){
    //TODO: add mutate node functionality
}

void mutateConnection(Genome* genome){
    
    
}


void mutate(Genome* genome){
    
    
    if(!hasSetSeed) {
        srand(time(NULL));

        hasSetSeed = true;
    }
    
    float max = 1.0f;
    float min = 0.0f;

    float temp = (float)(((float)(rand()) / (float)(RAND_MAX)) * (max - min) + min);
    
   

    if(temp < nodeMutationProbability){
        mutateNode(genome);
    }

    else{
        mutateConnection(genome);
    }
}   

