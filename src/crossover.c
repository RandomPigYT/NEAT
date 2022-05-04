#include "includes/NEAT.h"
#include "includes/NEAT_core.h"
#include <stdio.h>
#include <stdlib.h>

enum {
	GREATER,
	LESSER,
	EQUAL

};


uint32_t findNumCons(Genome* genome){

    uint32_t len = 0;
    for(uint32_t i = 0; i < genome->numberOfConnections; i++){

        if(!genome->connections[i].deleted) len++;
    }

    return len;
}



Connection* getCon(Genome* genome, uint32_t innovation){
    for (uint32_t i = 0; i < genome->numberOfConnections; i++)
    {
        if(genome->connections[i].innovation == innovation && !genome->connections[i].deleted) return &genome->connections[i];
    }
    return NULL;   
}

uint8_t cmpFitness(Genome* parent1, Genome* parent2){
	if(parent1->fitness > parent2->fitness){
		return GREATER;
	}
	else if(parent1->fitness < parent2->fitness){

		return LESSER;
	}

	else{
	
		return EQUAL;
	}

}

void crossover(Genome* parent1, Genome* parent2){
	
	uint8_t fitnessCmp = cmpFitness(parent1, parent2);

	Genome child;

	


}       
