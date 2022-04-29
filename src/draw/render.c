#include "drawHeaders/drawHeader.h"
#include <stdio.h>
#include <stdlib.h>

#define NODE_RADIUS 15.0f
#define LINE_SCALE_X 3.0f
#define LINE_SCALE_Y 3.0f


void display(){


    SDL_RenderPresent(renderer);
}

void render(SDL_Texture* texture, SDL_Rect dst){



    SDL_Rect src;

    src.x = 0;
    src.y = 0; 
    src.w = 721;
    src.h = 512;

    
    SDL_RenderCopy(renderer, texture, &src, &dst);
    SDL_DestroyTexture(texture);
}

SDL_Texture* loadTexture(const char* file){

  SDL_Texture* texture = NULL;

  texture = IMG_LoadTexture(renderer, file);

  if(texture == NULL){

    fprintf(stderr, "Failed to load texture. Error: %s\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }

  return texture;
    
    
}




void drawNode(Node* node){

  if(node->numInNodes == 0 && node->type != INPUT && node->type != OUTPUT && node->type != BIAS) return;

  Uint8 colour[4] = {26, 48, 138, 255};

  SDL_RenderFillCircle(renderer, node->pos[0], node->pos[1], NODE_RADIUS, colour);
  
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);


}

void drawCon(Connection* con){

  float xScale, yScale;
  SDL_RenderGetScale(renderer, &xScale, &yScale);



  if(con->type == FEED_FORWARD && con->isEnabled) {

    if(con->weight < 0.0f) thickLineRGBA(renderer, con->pos[0], con->pos[1], con->pos[2], con->pos[3], 3, 186, 43, 43, 255);
    if(con->weight > 0.0f) thickLineRGBA(renderer, con->pos[0], con->pos[1], con->pos[2], con->pos[3], 3, 41, 214, 87, 255);

  }

  else if(con->type == RECURRENT && con->isEnabled) thickLineRGBA(renderer, con->pos[0], con->pos[1], con->pos[2], con->pos[3], 3, 0, 0, 0, 255);

 
  
  
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);


  
}