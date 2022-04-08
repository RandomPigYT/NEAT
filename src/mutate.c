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

void initNodeMem(Genome* genome){
    if(genome->numberOfNodes == 0){
        genome->nodes = malloc(10 * sizeof(Node));
        genome->remainingNodeMem = 10;
    }
    else{
        if(genome->remainingNodeMem == 0){
            genome->nodes = realloc(genome->nodes, (genome->numberOfNodes + 10) * sizeof(Node));
            genome->remainingNodeMem = 10;
        }
    }
}


void addConnection(Genome* genome){

    printf("Adding connection\n");

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

    // Too lazy to create another function :p
    
    if(genome->nodes[in].numInNodes == 0){
       genome->nodes[in].inNodes = malloc(10 * sizeof(uint32_t));
        genome->nodes[in].remainingInNodeMem = 10;
    }
    else {
        if(genome->nodes[in].remainingInNodeMem == 0){
            genome->nodes[in].inNodes = realloc(genome->nodes[in].inNodes, (genome->nodes[in].numInNodes + 10) * sizeof(uint32_t));
            genome->nodes[in].remainingInNodeMem = 10;
        } 
    }

    genome->nodes[in].inNodes[genome->nodes[in].numInNodes] = genome->connections[genome->numberOfConnections].innovation;
    genome->nodes[in].remainingInNodeMem--;

    
    genome->numberOfConnections++;
    genome->remainingConMem--;

    sortToLayers(genome);

    return;
}

uint32_t findMaxIndex(Genome* genome){
    uint32_t max = 0;

    for(uint32_t i = 0; i < genome->numberOfNodes; i++){
        if(genome->nodes[i].index > max) max = genome->nodes[i].index;
    }

    return max;
}

uint32_t findNode(Genome* genome, uint32_t index){
    for(uint32_t i = 0; i < genome->numberOfNodes; i++){
        if(genome->nodes[i].index == index) return genome->nodes[i].index; 
    }
}

void addNode(Genome* genome){
    

    uint32_t conIndex = (int)(((float)(rand()) / RAND_MAX) * ((genome->numberOfConnections - 1) - 0) + 0);

    Node node = createNode(findMaxIndex(genome) + 1);

    initNodeMem(genome);

    genome->nodes[genome->numberOfNodes] = node;
    genome->remainingNodeMem--;
    genome->numberOfNodes++;

    genome->connections[conIndex].isEnabled = false;

    Connection con1 = createConnection(node.index, genome->connections[conIndex].outNode, FEED_FORWARD);
    con1.weight = 1;

    Connection con2 = genome->connections[conIndex];
    con2.outNode = node.index;
    setInnovation(&con2);

    initConMem(genome);
    
    genome->connections[genome->numberOfConnections] = con1;
    genome->numberOfConnections++;
    genome->remainingConMem--;

    initConMem(genome);

    genome->connections[genome->numberOfConnections] = con2;
    genome->numberOfConnections++;
    genome->remainingConMem--;
}



void mutateNode(Genome* genome){
    


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



