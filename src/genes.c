#include "includes/NEAT.h"
#include "includes/NEAT_core.h"
#include <stdio.h>
#include <stdlib.h>

Node createNode(uint32_t index, uint8_t type){
    Node node;


    return node;    
}


Connection createConnection(uint32_t inNode, uint32_t outNode, uint32_t innovation, uint8_t type){
    Connection con;

    con.inNode = inNode;
    con.outNode = outNode;
    
    con.type = type;

    con.isEnabled = true;


    float max = 1.0f;
    float min = -1.0f;

    con.weight = ((float) rand() / RAND_MAX) * (max - min) + min;

    con.innovation = innovation;
    return con;
}