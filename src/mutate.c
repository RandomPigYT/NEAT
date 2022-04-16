#include "includes/NEAT.h"
#include "includes/NEAT_core.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

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



void initInNodeMem(Node* node){

    if(node->remainingInNodeMem == 0){

        node->inNodes = realloc(node->inNodes, (node->numInNodes + 10) * sizeof(uint32_t));
        
        node->remainingInNodeMem = 10;
    }
}

BOOL addConnection(Genome* genome){

    
    uint32_t to = (int)(((float)(rand()) / RAND_MAX) * ((genome->numberOfNodes - 1) - 0) + 0);
    uint32_t from = (int)(((float)(rand()) / RAND_MAX) * ((genome->numberOfNodes - 1) - 0) + 0);

    if(genome->nodes[to].layer == genome->nodes[from].layer) return false;

    uint8_t type = genome->nodes[from].layer < genome->nodes[to].layer ? FEED_FORWARD : RECURRENT;
    Connection con = createConnection(genome->nodes[to].index, genome->nodes[from].index, type);

    
    

    for(int i = 0; i < genome->numberOfConnections; i++){
        if(con.innovation == genome->connections[i].innovation) return false; 
    }
    
    initInNodeMem(&(genome->nodes[to]));
    uint32_t nInNodes = genome->nodes[to].numInNodes;

    genome->nodes[to].inNodes[nInNodes] = con.innovation;
    genome->nodes[to].remainingInNodeMem--;
    genome->nodes[to].numInNodes++;

    initConMem(genome);

    genome->connections[genome->numberOfConnections] = con;
    genome->numberOfConnections++;
    genome->remainingConMem--;


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




void addNodeMut(Genome* genome){
    
    uint32_t conIndex = (int)(((float)(rand()) / RAND_MAX) * ((genome->numberOfConnections - 1) - 0) + 0);
    
    Connection* cPtr = &(genome->connections[conIndex]);
    cPtr->isEnabled = false;

    Node node = createNode(findMaxIndex(genome));
    
    // Create the connections
    Connection con1 = createConnection(node.index, cPtr->from, FEED_FORWARD);
    con1.weight = 1.0f;

    Connection con2 = createConnection(cPtr->to, node.index, cPtr->type);
    con2.weight = cPtr->weight;

    initInNodeMem(&node);

    node.inNodes[node.numInNodes] = cPtr->from;
    node.numInNodes++;
    node.remainingInNodeMem--;
    
    // Add a reference of the new node to the old node
    uint32_t tempNodeIndex = findNode(genome, cPtr->to);
    initInNodeMem(&(genome->nodes[tempNodeIndex]));
    genome->nodes[tempNodeIndex].inNodes[genome->nodes[tempNodeIndex].numInNodes - 1] = node.index;

    

    // Add the node to the genome
    initNodeMem(genome);
    genome->nodes[genome->numberOfNodes] = node;
    genome->numberOfNodes++;
    genome->remainingNodeMem--;

    // Add the connections into the genome
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
    
    addNodeMut(genome);

}

void mutateConnection(Genome* genome){
    for(int i = 0; i < 100; i++){
        BOOL addedCon = addConnection(genome);
        if(addedCon) return;
    }
   // printf("Con not possible\n");
    
    return;
}


void mutate(Genome* genome){
    
    
    if(!hasSetSeed) {
        srand(time(NULL));

        hasSetSeed = true;
    }
    
    float max = 1.0f;
    float min = 0.0f;

    float temp = (float)(((float)(rand()) / (float)(RAND_MAX)) * (max - min) + min);
    
    if(genome->numberOfConnections == 0) addConnection(genome);
     
    else{
    
        if(temp < nodeMutationProbability){
            mutateNode(genome);
        }

        else{
            mutateConnection(genome);
        }
    
     }

   return;
}   



