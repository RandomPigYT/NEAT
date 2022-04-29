#include "drawHeaders/drawHeader.h"



/*
* Copyright 2016 Gumichan01
*
* Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated 
* documentation files (the "Software"), to deal in the Software without restriction, including without limitation the 
* rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to 
* permit persons to whom the Software is furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in all copies or substantial portions of the 
* Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO
* THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
* CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER 
* DEALINGS IN THE SOFTWARE.
*
*/

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