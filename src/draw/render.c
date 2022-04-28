#include "drawHeaders/drawHeader.h"
#include <stdio.h>
#include <stdlib.h>

#define NODE_RADIUS 8.0f
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

int SDL_RenderDrawCircle(SDL_Renderer * renderer, float x, float y, float radius, Uint8 color[4])
{
  SDL_SetRenderDrawColor(renderer, color[0], color[1], color[2], color[3]);

    float offsetx, offsety, d;
    int status;

    //CHECK_RENDERER_MAGIC(renderer, -1);

    offsetx = 0.0f;
    offsety = radius;
    d = radius -1;
    status = 0;

    while (offsety >= offsetx) {
        status += SDL_RenderDrawPointF(renderer, x + offsetx, y + offsety);
        status += SDL_RenderDrawPointF(renderer, x + offsety, y + offsetx);
        status += SDL_RenderDrawPointF(renderer, x - offsetx, y + offsety);
        status += SDL_RenderDrawPointF(renderer, x - offsety, y + offsetx);
        status += SDL_RenderDrawPointF(renderer, x + offsetx, y - offsety);
        status += SDL_RenderDrawPointF(renderer, x + offsety, y - offsetx);
        status += SDL_RenderDrawPointF(renderer, x - offsetx, y - offsety);
        status += SDL_RenderDrawPointF(renderer, x - offsety, y - offsetx);
        
        if (status < 0) {
            status = -1;
            break;
        }

        if (d >= 2*offsetx) {
            d -= 2*offsetx + 1;
            offsetx +=1;
        }
        else if (d < 2 * (radius - offsety)) {
            d += 2 * offsety - 1;
            offsety -= 1;
        }
        else {
            d += 2 * (offsety - offsetx - 1);
            offsety -= 1;
            offsetx += 1;
        }
    }

    return status;
}


int
SDL_RenderFillCircle(SDL_Renderer * renderer, float x, float y, float radius, Uint8 color[4])
{

  SDL_SetRenderDrawColor(renderer, color[0], color[1], color[2], color[3]);
    
    float offsetx, offsety, d;
    int status;

    //CHECK_RENDERER_MAGIC(renderer, -1);

    offsetx = 0.0f;
    offsety = radius;
    d = radius -1;
    status = 0;

    while (offsety >= offsetx) {

        status += SDL_RenderDrawLineF(renderer, x - offsety, y + offsetx,
                                     x + offsety, y + offsetx);
        status += SDL_RenderDrawLineF(renderer, x - offsetx, y + offsety,
                                     x + offsetx, y + offsety);
        status += SDL_RenderDrawLineF(renderer, x - offsetx, y - offsety,
                                     x + offsetx, y - offsety);
        status += SDL_RenderDrawLineF(renderer, x - offsety, y - offsetx,
                                     x + offsety, y - offsetx);

        if (status < 0) {
            status = -1;
            break;
        }

        if (d >= 2*offsetx) {
            d -= 2*offsetx + 1;
            offsetx +=1;
        }
        else if (d < 2 * (radius - offsety)) {
            d += 2 * offsety - 1;
            offsety -= 1;
        }
        else {
            d += 2 * (offsety - offsetx - 1);
            offsety -= 1;
            offsetx += 1;
        }
    }

    return status;
}

void drawNode(Node* node){

  Uint8 colour[4] = {26, 48, 138, 255};

  SDL_RenderFillCircle(renderer, node->pos[0], node->pos[1], NODE_RADIUS, colour);
  
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

  char* index[100];
  SDL_itoa(node->index, index, 10);
  
  SDL_Color c = {.r = 255, .g = 255, .b = 255, .a = 255};
  SDL_Surface* text;
  SDL_Texture* texture;
  SDL_Rect rect = {.h = 4, .w = 2, .x = node->pos[0] - 1, .y = node->pos[1] - 2};

  text = TTF_RenderText_Solid("roboto.ttf", index, c);

  if(text == NULL) fprintf(stderr, "failed to load text. Error: %s", TTF_GetError()); exit(EXIT_FAILURE);
  free(index);

  texture = SDL_CreateTextureFromSurface(renderer, text);

  SDL_FreeSurface(text);
  render(texture, rect);
}

void drawCon(Connection* con){

  float xScale, yScale;
  SDL_RenderGetScale(renderer, &xScale, &yScale);

  Uint8* colour = malloc(4 * sizeof(Uint8));

  if(con->type == FEED_FORWARD) {

    if(con->weight < 0) colour[0] = 133; colour[1] = 34; colour[2] = 34, colour[3] = 255;
    if(con->weight > 0) colour[0] = 43; colour[1] = 148; colour[2] = 45, colour[3] = 255;
  }

  else colour[0] = 0; colour[1] = 0; colour[2] = 0, colour[3] = 255;

  if(con->isEnabled){
    thickLineRGBA(renderer, con->pos[0], con->pos[1], con->pos[2], con->pos[3], 3, colour[0], colour[1], colour[2], colour[3]);

  }
  
  
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  free(colour);

  
}