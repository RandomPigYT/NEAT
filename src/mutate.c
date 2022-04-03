#include "includes/NEAT.h"
#include "includes/NEAT_core.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

float connectionMutationProb = 0.8f;
float nodeMutationProbability = 0.2f;

BOOL hasSetSeed = false;

void mutateNode(Genome* genome){
    //TODO: add mutate node functionality
}

void mutateConnection(Genome* genome){
    
    //TODO: add mutate connection functionality

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

