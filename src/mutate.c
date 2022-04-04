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




void addConnection(Genome* genome){

    BOOL outNodeExists = false;
    BOOL inNodeExists = false;

   

    uint32_t out = ((int) rand() / RAND_MAX) * genome->numberOfNodes - 1;
    uint32_t in = ((int) rand() / RAND_MAX) * genome->numberOfNodes - 1;

    

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
}   

double a = 0.0;
