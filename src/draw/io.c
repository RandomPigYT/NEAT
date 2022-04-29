#include "drawHeaders/drawHeader.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef char int_8; 


void updateConCoords(){

    for(uint32_t i = 0; i < currentGenome->numberOfConnections; i++){

        currentGenome->connections[i].pos[0] = getNode(currentGenome->connections[i].from, currentGenome).pos[0];
        currentGenome->connections[i].pos[1] = getNode(currentGenome->connections[i].from, currentGenome).pos[1];
        currentGenome->connections[i].pos[2] = getNode(currentGenome->connections[i].to, currentGenome).pos[0];
        currentGenome->connections[i].pos[3] = getNode(currentGenome->connections[i].to, currentGenome).pos[1];
    }
}
void transformNode(int32_t x, int32_t y){

    if(grabbedNode != NULL){

        grabbedNode->pos[0] = x;
        grabbedNode->pos[1] = y;
        return;
    }
    

    for(uint32_t i = 0; i < currentGenome->numberOfNodes; i++){
        
        float op1 = pow((x - currentGenome->nodes[i].pos[0]), 2);
        float op2 = pow((y - currentGenome->nodes[i].pos[1]), 2);

        float dist = sqrt(op1 + op2);
         
         if(dist <= 15) {
             currentGenome->nodes[i].pos[0] = x;
             currentGenome->nodes[i].pos[1] = y;
             grabbedNode = &(currentGenome->nodes[i]);
             return;
         }
    }    

}



void moveNodeWithMouse(int32_t x, int32_t y){

    transformNode(x, y);
    
    updateConCoords();
}