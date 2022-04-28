#include "includes/NEAT.h"
#include "includes/NEAT_core.h"
#include <stdio.h>
#include <stdlib.h>


#define WIDTH_START_COORD 78
#define WIDTH_END_COORD 550



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


void verifyRecurrentCons(Genome* genome){

    for(uint32_t i = 0; i < genome->numberOfConnections; i++){

        if(genome->connections[i].type == RECURRENT){
            Node to = getNode(genome->connections[i].to, genome);
            Node from = getNode(genome->connections[i].from, genome);

            if(to.layer == from.layer) genome->connections[i].isEnabled = false;
            else if(from.layer < to.layer) genome->connections[i].type = FEED_FORWARD;
        }
    }
}
uint32_t recursiveSort(Node node, uint32_t currentLayer, Genome* genome){
    if(node.type == INPUT || node.type == BIAS) return currentLayer;

    // {
    //     BOOL tempBool = false;

    //     for(uint32_t i = 0; i < node.numInNodes; i++){
    //         if(findCon(node.index, node.inNodes[i], genome).type == FEED_FORWARD) tempBool = true;
    //     }

    //     if(!tempBool) currentLayer--;
    // }

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



void setCoords(Genome* genome){

    // Sets the coordinates of the nodes according to their layer
    float offset;

    offset =  (WIDTH_START_COORD + WIDTH_END_COORD) / genome->numberOfLayers;

    for(uint32_t i = 0; i < genome->numberOfNodes; i++){
        genome->nodes[i].pos[0] = offset * genome->nodes[i].layer + WIDTH_START_COORD;
    }

    // Sets coords of the connections
    for(uint32_t i = 0; i < genome->numberOfConnections; i++){

        genome->connections[i].pos[0] = getNode(genome->connections[i].from, genome).pos[0];
        genome->connections[i].pos[1] = getNode(genome->connections[i].from, genome).pos[1];
        genome->connections[i].pos[2] = getNode(genome->connections[i].to, genome).pos[0];
        genome->connections[i].pos[3] = getNode(genome->connections[i].to, genome).pos[1];
    }

}


void sortToLayers(Genome* genome){
    
    uint32_t maxLayers = 1;
    // Load the input nodes into the buffer to sort
    
    for(uint32_t i = 0; i < genome->numberOfNodes; i++){
        genome->nodes[i].layer = recursiveSort(genome->nodes[i], 0, genome);
    }

    uint32_t outputLayer = findMaxLayer(genome) + 1;
    
    for(uint32_t i = 0; i < genome->numberOfNodes; i++){
        if(genome->nodes[i].type == OUTPUT) genome->nodes[i].layer = outputLayer;
    }

    genome->numberOfLayers = outputLayer;
    
    verifyRecurrentCons(genome);

    setCoords(genome);
    return;
}



