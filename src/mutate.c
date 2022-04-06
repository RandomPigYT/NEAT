#include "includes/NEAT.h"
#include "includes/NEAT_core.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>

float connectionMutationProb = 0.8f;
float nodeMutationProbability = 0.2f;

BOOL hasSetSeed = false;


void initConMem(Genome* genome){

    if(genome->numberOfConnections == 0){
        genome->connections = malloc(10 * sizeof(Connection));
        genome->remainingConMem = 10;
    }

    else{
        if(genome->remainingConMem == 0){
            genome->connections = realloc(genome->connections, (genome->numberOfConnections + 10) * sizeof(Connection));
            genome->remainingConMem = 10;
        }
    }

    return;
}


void addConnection(Genome* genome){

    uint8_t type;

    uint32_t out = (int)(((float)(rand()) / RAND_MAX) * ((genome->numberOfNodes - 1) - 0) + 0);
    uint32_t in = (int)(((float)(rand()) / (float)(RAND_MAX)) * ((genome->numberOfNodes - 1) - 0) + 0);
    initConMem(genome);


    if(genome->nodes[out].layer >= genome->nodes[in].layer){
        type = RECURRENT;
    }
    else{
        type = FEED_FORWARD;
    }

    uint32_t inIndex = genome->nodes[in].index;
    uint32_t outIndex = genome->nodes[out].index;
    
    

    
    genome->connections[genome->numberOfConnections] = createConnection(inIndex, outIndex, type);

    genome->numberOfConnections++;
    genome->remainingConMem--;

    

    return;
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
    
   addConnection(genome);

 /*   if(temp < nodeMutationProbability){
        mutateNode(genome);
    }

    else{
        mutateConnection(genome);
    }
    */

   return;
}   



