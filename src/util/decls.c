#include "../includes/NEAT.h"
#include "../includes/NEAT_core.h"
#include "../draw/drawHeaders/drawHeader.h"



// Tentative declarations of all the global variables
Genome* population;
uint32_t popSize;



uint32_t globalInnovationNumber;

Memory* geneMemory;
uint32_t numGenesInMemory;
uint32_t remainingMemory;   



uint32_t numInputs;
uint32_t numOutputs;

BOOL isPaused;

Genome* currentGenome;

SDL_Window *window;
SDL_Renderer* renderer;

Node* grabbedNode;


