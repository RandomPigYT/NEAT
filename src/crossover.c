#include "includes/NEAT.h"
#include "includes/NEAT_core.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
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
        if(genome->connections[i].innovation == innovation && !genome->connections[i].deleted) return i;
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


Genome cloneGenome(Genome* genome){
	Genome clone;
	
	clone = *genome;
	
	clone.nodes = malloc(genome->numberOfNodes * sizeof(Node));
	clone.connections = malloc(genome->numberOfConnections * sizeof(Connection));

	memcpy(clone.nodes, genome->nodes, genome->numberOfNodes * sizeof(Node));
	memcpy(clone.connections, genome->connections, genome->numberOfConnections * sizeof(Connection));
	

	// Since only the connections are copied without also copying the free memory, the fields that keep track of the Genome's memory must also be updated 
	clone.numberOfConnections = genome->numberOfConnections;
	clone.numberOfNodes = genome->numberOfNodes;

	clone.remainingConMem = 0;
	clone.remainingNodeMem = 0;

	return clone;
	
}

void removeDeletedCons(Genome* genome){
	Connection* buf = malloc(genome->numberOfConnections * sizeof(Connection));
	uint32_t index = 0;

	for(uint32_t i = 0; i < genome->numberOfConnections; i++){
		if(!genome->connections[i].deleted){
			buf[index] = genome->connections[i];
			index++;
		}
	}

	free(genome->connections);
	genome->connections = buf;
}



void buildGenome(Genome* genome){
	// This function is only really used if the genomes have equal fitness. 
	
}



Genome crossover(Genome* parent1, Genome* parent2){
	
	uint8_t fitnessCmp = cmpFitness(parent1, parent2);

	Genome child;
	
	quickSort(parent1, INNOVATION);
	quickSort(parent2, INNOVATION);
	


	if(fitnessCmp == GREATER){
		child = cloneGenome(parent1);
		removeDeletedCons(&child);
		
		for(uint32_t i = 0; i < child.numberOfConnections; i++){
			int32_t temp = getCon(parent2, child.connections[i].innovation);
			if(temp > 0){
				
				float random = ((float)rand() / (float)RAND_MAX) * (1.0f - 0.0f) + 0.0f;
				
				if(random < 0.5f){
					child.connections[i] = parent2->connections[temp];
				}
			}
		}
	}
	
	if(fitnessCmp == LESSER){
		child = cloneGenome(parent2);
		removeDeletedCons(&child);
		
		for(uint32_t i = 0; i < child.numberOfConnections; i++){
			int32_t temp = getCon(parent1, child.connections[i].innovation);
			if(temp > 0){
				
				float random = ((float)rand() / (float)RAND_MAX) * (1.0f - 0.0f) + 0.0f;
				
				if(random < 0.5f){
					child.connections[i] = parent1->connections[temp];
				}
			}
		}
	}
	
	if(fitnessCmp == EQUAL){
			

	}


	return child;
}       

