#include "../includes/NEAT.h"
#include "../includes/NEAT_core.h"
#include <stdlib.h>

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


void initInNodeMem(Node* node){

    if(node->remainingInNodeMem == 0){

        node->inNodes = realloc(node->inNodes, (node->numInNodes + 10) * sizeof(uint32_t));

        node->remainingInNodeMem = 10;
    }
}
