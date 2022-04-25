#include "includes/NEAT.h"
#include "includes/NEAT_core.h"
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void createWindow(void* arg){

  SDL_Window *window = NULL;

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "SDL failed to initialise: %s\n", SDL_GetError());
        return 1;
    }


    window = SDL_CreateWindow("Hello", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 500, 500, SDL_WINDOW_RESIZABLE);

    SDL_Event e;
   for(;;)
   {
       while( SDL_PollEvent(&e) != 0 ) {
    if( e.type == SDL_QUIT ) {
      SDL_DestroyWindow(window);
      goto quit;
    }
  } // en
   }
   
   quit:
     SDL_Quit();
}

void draw(void* args){
    
    pthread_t id;

    pthread_create(&id, NULL, createWindow, NULL);

    pthread_join(id, NULL);

    return;
}