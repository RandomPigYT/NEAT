#include "../includes/NEAT.h"
#include "../includes/NEAT_core.h"
#include <stdlib.h>
#include <stdio.h>

void swap(uint32_t a, uint32_t b, Genome* genome){
    
   

    Connection temp = genome->connections[a];

    genome->connections[a] = genome->connections[b];
    genome->connections[b] = temp;
}


int32_t sort(Genome* genome, int32_t start, int32_t end){
    
   

    if(start >= end) return -1;

    int32_t j = start - 1;
    int32_t pivot = end;

    for(uint32_t i = 0; i < end; i++){

        if(genome->connections[i].innovation > genome->connections[pivot].innovation) continue;

        j++;

        swap(j, i, genome);
        
    }

    j++;
    swap(j, pivot, genome);

    pivot = j;

   

    sort(genome, start, pivot - 1);
    sort(genome, pivot + 1, end);


}

// Test function



void quickSort(Genome* genome, uint32_t type){


        

    if(type == INNOVATION) sort(genome, 0, genome->numberOfConnections - 1);
    


       
     
   
}