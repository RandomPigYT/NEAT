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


//==================================================================================================================================================


void removeCon(Genome* genome, uint32_t innovation){

    

}


BOOL addConnection(Genome* genome){

    
    uint32_t to = (int)(((float)(rand()) / RAND_MAX) * ((genome->numberOfNodes - 1) - 0) + 0);
    uint32_t from = (int)(((float)(rand()) / RAND_MAX) * ((genome->numberOfNodes - 1) - 0) + 0);

    if(genome->nodes[to].layer == genome->nodes[from].layer) return false;

    uint8_t type = genome->nodes[from].layer < genome->nodes[to].layer ? FEED_FORWARD : RECURRENT;

    

    Connection con = createConnection(genome->nodes[to].index, genome->nodes[from].index, type);

    

    for(int i = 0; i < genome->numberOfConnections; i++){
        if(con.innovation == genome->connections[i].innovation) {
			
			if(genome->connections[i].deleted) genome->connections[i].deleted = false; return true;

			return false;
		}
		
    }
    
    float recurrentProb = ((float) rand() / RAND_MAX) * (1.0f - 0.0f) + 0.0f;
    printf("recurrentProb: %f\n", recurrentProb);
    if(recurrentProb > 0.4f && type == RECURRENT) return false; 

    // Set its coords

    con.pos[0] = genome->nodes[from].pos[0];
    con.pos[1] = genome->nodes[from].pos[1];
    con.pos[2] = genome->nodes[to].pos[0];    
    con.pos[3] = genome->nodes[to].pos[1];    
    

    initInNodeMem(&(genome->nodes[to]));
    uint32_t nInNodes = genome->nodes[to].numInNodes;

    genome->nodes[to].inNodes[nInNodes] = con.from;
    genome->nodes[to].remainingInNodeMem--;
    genome->nodes[to].numInNodes++;

    initConMem(genome);

    genome->connections[genome->numberOfConnections] = con;
    genome->numberOfConnections++;
    genome->remainingConMem--;

    return true;
}



void removeNodeMut(Genome* genome){

    if(genome->numberOfNodes == numInputs + numOutputs) return;

    uint32_t nodeIndex = (int)(((float)(rand()) / RAND_MAX) * ((genome->numberOfNodes - 1) - (numInputs + numOutputs)) + (numInputs + numOutputs));

    Node* nPtr = &(genome->nodes[nodeIndex]);

    
    for(uint32_t i = 0; i < genome->numberOfConnections; i++){
        
         if(genome->connections[i].to == nPtr->index || genome->connections[i].from == nPtr->index){
            
            genome->connections[i].deleted = true;
         }
    }


    

    free(nPtr->inNodes);

    if(nodeIndex == genome->numberOfNodes - 1 && genome->nodes[nodeIndex].index != nPtr->index){
        free(genome->nodes[nodeIndex].inNodes);

        genome->numberOfNodes--;
        genome->remainingNodeMem++;

        return;
    }

    for(uint32_t i = nodeIndex + 1; i < genome->numberOfNodes; i++){

        genome->nodes[i - 1] = genome->nodes[i];
    }


    genome->numberOfNodes--;
    genome->remainingNodeMem++;
}






void addNodeMut(Genome* genome){
    
    uint32_t conIndex = (int)(((float)(rand()) / RAND_MAX) * ((genome->numberOfConnections - 1) - 0) + 0);
    
    Connection* cPtr = &(genome->connections[conIndex]);
    cPtr->isEnabled = false;

    Node node = createNode(findMaxIndex(genome) + 1);
    
    float xOff, yOff;


    yOff = ((float) rand() / RAND_MAX) * (50.0f - (-50.0f)) + (-50.0f);


    node.pos[0] = ((cPtr->pos[0] + cPtr->pos[2]) / 2);
    node.pos[1] = ((cPtr->pos[1] + cPtr->pos[3]) / 2) + yOff;

    // Create the connections
    Connection con1 = createConnection(node.index, cPtr->from, cPtr->type);
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
    genome->nodes[tempNodeIndex].inNodes[genome->nodes[tempNodeIndex].numInNodes] = node.index;
    genome->nodes[tempNodeIndex].numInNodes++;
    genome->nodes[tempNodeIndex].remainingInNodeMem--;


    // BOOL is = false;

    // for(uint32_t i = 0; i < genome->nodes[tempNodeIndex].numInNodes; i++){
    //     if(genome->nodes[tempNodeIndex].inNodes[i] == cPtr->from){
    //         is = true;
    //         genome->nodes[tempNodeIndex].inNodes[i] = node.index;
    //     }
    // }
    
    // assert(is != false);
    
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

    sortToLayers(genome);

}



void mutateNode(Genome* genome){
    
    addNodeMut(genome);

}

void mutateConnection(Genome* genome){
    for(int i = 0; i < 20; i++){
        BOOL addedCon = addConnection(genome);
        if(addedCon) return;
    }

    
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



