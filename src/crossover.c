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



int32_t getCon(Genome* genome, uint32_t innovation){
    for (uint32_t i = 0; i < genome->numberOfConnections; i++)
    {
        if(genome->connections[i].innovation == innovation && !genome->connections[i].deleted) return &genome->connections[i];
    }
    return -1;   
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

Genome crossover(Genome* parent1, Genome* parent2){
	
	uint8_t fitnessCmp = cmpFitness(parent1, parent2);

	Genome child;
	
	uint32_t fitterGenomeSize;

	if(fitnessCmp == GREATER) {
		child.connections = malloc(parent1->numberOfConnections * sizeof(Connection));
		child.numberOfConnections = parent1->numberOfConnections;
		fitterGenomeSize = parent1->numberOfConnections;
	}

	else if(fitnessCmp == LESSER) {
		child.connections = malloc(parent2->numberOfConnections * sizeof(Connection));
		child.numberOfConnections = parent2->numberOfConnections;
		
		fitterGenomeSize = parent2->numberOfConnections;
	}
	
	else{
		
		if(findNumCons(parent1) >= findNumCons(parent2)){

			child.connections = malloc(parent1->numberOfConnections * sizeof(Connection));
			child.numberOfConnections = parent1->numberOfConnections;

			fitterGenomeSize = parent1->numberOfConnections;
		}
		
		else{
			
			child.connections = malloc(parent2->numberOfConnections * sizeof(Connection));
			child.numberOfConnections = parent2->numberOfConnections;

			fitterGenomeSize = parent2->numberOfConnections;

		}

		
	}
	

	for(uint32_t i = 0; i <  fitterGenomeSize; i++){


	}


}       
