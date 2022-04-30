#ifndef DRAW_HEADER_H
#define DRAW_HEADER_H

#include "../../includes/NEAT.h"
#include "../../includes/NEAT_core.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL2_gfxPrimitives.h>




typedef struct dst_t{
    int x;
    int y;
    int w;
    int h;

} Dst;

typedef struct src_t{
    int x;
    int y;
    int w;
    int h;

} Src;


typedef struct {
    
    const char* title;
    int x;
    int y;
    int w;
    int h;
    Uint32 flags;
} WindowData;

typedef struct entity_t{

    
    
    Node* node;

    Dst dst;
} NodeEntity;

typedef struct texture_t{
    
    Src src;
}Texture;

Genome* currentGenome;


SDL_Window *window;
SDL_Renderer* renderer;

Node* grabbedNode;

void render(SDL_Texture* texture, SDL_Rect dst);
void display();
SDL_Texture* loadTexture(const char* file);
int SDL_RenderDrawCircle(SDL_Renderer * renderer, float x, float y, float radius, Uint8* color);
int SDL_RenderFillCircle(SDL_Renderer * renderer, float x, float y, float radius, Uint8* color);

void drawNode(Node* node);
void drawCon(Connection* con);


void moveNodeWithMouse(int32_t x, int32_t y);

#endif  //DRAW_HEADER_H

