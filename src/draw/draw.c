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



void createWindow(void* arg){
  
  TTF_WasInit();

  if(TTF_Init() != 0){
    fprintf(stderr, "Failed to initialize ttf. Error: %s", TTF_GetError());
    exit(EXIT_FAILURE);
  }

 
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
  
  
  while (!shouldClose){
    
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
   
  TTF_Quit();
  SDL_Quit();

}

void draw(void* args){

    pthread_t id;

  WindowData windowData = {.title = "NEAT", .x = SDL_WINDOWPOS_UNDEFINED, .y = SDL_WINDOWPOS_UNDEFINED, .w = 750, .h = 500, .flags = SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN};

  Data d = {.w = windowData, .genome = (Genome*)args};

    
    pthread_create(&id, NULL, createWindow, &d);

    pthread_join(id, NULL);

    return;
}