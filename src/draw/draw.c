#include "../includes/NEAT.h"
#include "../includes/NEAT_core.h"
#include "drawHeaders/drawHeader.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>


typedef struct data_t
{
  WindowData w;
  Genome* genome;
} Data;


void updateCoords(){

    // Sets the coordinates of the nodes according to their layer


    // Sets coords of the connections
    for(uint32_t i = 0; i < currentGenome->numberOfConnections; i++){

        currentGenome->connections[i].pos[0] = getNode(currentGenome->connections[i].from, currentGenome).pos[0];
        currentGenome->connections[i].pos[1] = getNode(currentGenome->connections[i].from, currentGenome).pos[1];
        currentGenome->connections[i].pos[2] = getNode(currentGenome->connections[i].to, currentGenome).pos[0];
        currentGenome->connections[i].pos[3] = getNode(currentGenome->connections[i].to, currentGenome).pos[1];
    }

}


void createWindow(void* arg){
  







 
  Data* data = arg;

  Genome* genome = data->genome;

  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
      fprintf(stderr, "SDL failed to initialise window: %s\n", SDL_GetError());
      exit(EXIT_FAILURE);
  }

  if(IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) == 0){
    fprintf(stderr, "Error intitializing image: %s", SDL_GetError());

    exit(EXIT_FAILURE); 
  }

  // Bad name for the struct since most of the fields are one letter long
  window = SDL_CreateWindow(data->w.title, data->w.x, data->w.y, data->w.w, data->w.h, data->w.flags);


  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  SDL_Event e;

  BOOL shouldClose = false; 
  
    currentGenome = genome; 
  
  while (!shouldClose){
    
    // TODO: Add function to choose fittest genome

    updateCoords();

    int32_t x, y;

    Uint32 mouseState = SDL_GetMouseState(&x, &y);

    if(mouseState & SDL_BUTTON_LMASK ) moveNodeWithMouse(x, y);
    
    else grabbedNode = NULL;


 
    while (SDL_PollEvent(&e)){
      if(e.type == SDL_QUIT) shouldClose = true;
      
    }

  for(uint32_t i = 0; i < genome->numberOfConnections; i++){
      drawCon(&(genome->connections[i]));
    }

    for(uint32_t i = 0; i < genome->numberOfNodes; i++){

      drawNode(&(genome->nodes[i]));
    }
  
  
  
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    display();
     SDL_RenderClear(renderer);
    
  }
  
  SDL_DestroyWindow(window);
   

  SDL_Quit();

}

pthread_t draw(void* args){

    pthread_t id;

  WindowData windowData = {.title = "NEAT", .x = SDL_WINDOWPOS_UNDEFINED, .y = SDL_WINDOWPOS_UNDEFINED, .w = 750, .h = 500, .flags = SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN};

  Data d = {.w = windowData, .genome = (Genome*)args};

    
    pthread_create(&id, NULL, createWindow, &d);


  pthread_join(id, NULL);
    return;
}
