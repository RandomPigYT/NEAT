#include "includes/NEAT.h"
#include "includes/NEAT_core.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>




int main(int argc, char** argv){
    srand(time(NULL));

    pthread_t id;


    createPopulation(3, 4, 10);

    pthread_create(&id, NULL, draw, population);

    mutateConnection(population);

    mutateConnection(population);




   for(int i = 0; i < 10; i++){

    float prob = ((float)(rand())/ RAND_MAX) * (1.0f);
    if(prob < 0.3f) mutateNode(population);
    
    else mutateConnection(population);
    //sleep(1);
   }


    for(int i = 0; i < population->numberOfConnections; i++){
       if(population->connections[i].deleted) printf("(deleted)\n");
       else if(!population->connections[i].isEnabled) printf("%c %d -> %d (disabled)\n", population->connections[i].weight >= 0 ? '+': '-', population->connections[i].from, population->connections[i].to);
        
        else printf("%c %d -> %d\t\t%s\t%f\n", population->connections[i].weight >= 0 ? '+': '-' ,population->connections[i].from, population->connections[i].to, population->connections[i].type == FEED_FORWARD ? "":"Recurrent", population->connections[i].weight);
    }


    printf("\n");

    for(int i = 0; i < population->numberOfNodes; i++){
      
        if(population->nodes[i].numInNodes == 0) printf("%d\t---\n", population->nodes[i].index);
        else{
            printf("%d\t", i);
            for(int j = 0; j < population->nodes[i].numInNodes; j++){
                printf("%d ", population->nodes[i].inNodes[j]);
            }
            printf("\n");
        }
    }

    printf("\n");



    for(int i = 0; i < population->numberOfNodes; i++){
        printf("%d\t%d\n",population->nodes[i].index, population->nodes[i].layer);
    }

    // for(int i = 0; i < 20; i++){
    //     removeNodeMut(population);
    //     sleep(1);
    // }
	
   for(int i = 0; i < 10; i++){

    float prob = ((float)(rand())/ RAND_MAX) * (1.0f);
    if(prob < 0.3f) mutateNode(&population[1]);
    
    else mutateConnection(&population[1]);
    //sleep(1);
   }



    population[0].fitness = 1.5f;
    population[1].fitness = 2.5f;

	

   

	usleep(500000);	

   *population =  crossover(population, &population[1]);
	pthread_join(id, NULL);
}
