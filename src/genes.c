#include "includes/NEAT.h"
#include "includes/NEAT_core.h"
#include <stdio.h>
#include <stdlib.h>

Node createNode(uint32_t index, uint8_t type){
    Node node;


    return node;    
}

void setInnovation(Connection* con){
    BOOL exists = false;
    uint32_t index;

    for(uint32_t i = 0; i < numGenesInMemory; i++){
        if(con->inNode == geneMemory[i].in && con->outNode == geneMemory[i].out){
            exists = true;
            index = i;
        }
        
    }

    if(exists){
        con->innovation = geneMemory[index].innovation;
        
    }

    else {
        if(numGenesInMemory == 0){
            geneMemory = malloc(10 * sizeof(Memory));

            remainingMemory = 10;

            geneMemory[numGenesInMemory].in = con->inNode;
            geneMemory[numGenesInMemory].out = con->outNode;

            globalInnovationNumber++;

            con->innovation = globalInnovationNumber;

            geneMemory[numGenesInMemory].innovation = globalInnovationNumber;

            numGenesInMemory++;
            remainingMemory--;

            
        }

        else {
            if(remainingMemory != 0){
                geneMemory[numGenesInMemory].in = con->inNode;
                geneMemory[numGenesInMemory].out = con->outNode;

                globalInnovationNumber++;

                con->innovation = globalInnovationNumber;

                geneMemory[numGenesInMemory].innovation = globalInnovationNumber;

                numGenesInMemory++;
                remainingMemory--;

            }

            else {
                geneMemory = realloc(geneMemory, (numGenesInMemory + 10) * sizeof(Memory));
                
                remainingMemory = 10;
                 
                geneMemory[numGenesInMemory].in = con->inNode;
                geneMemory[numGenesInMemory].out = con->outNode;

                globalInnovationNumber++;

                con->innovation = globalInnovationNumber;

                geneMemory[numGenesInMemory].innovation = globalInnovationNumber;

                numGenesInMemory++;
                remainingMemory--;
            }
        }
    }

    return;
}


Connection createConnection(uint32_t inNode, uint32_t outNode, uint8_t type){
    Connection con;

    con.inNode = inNode;
    con.outNode = outNode;
    
    con.type = type;

    con.isEnabled = true;


    float max = 1.0f;
    float min = -1.0f;

    con.weight = ((float) rand() / RAND_MAX) * (max - min) + min;

    
    setInnovation(&con);

    
    return con;
}

