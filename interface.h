#ifndef INTERFACE_H
#define INTERFACE_H

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h> //sudo apt install libsdl2-2.0-0 libsdl2-gfx-1.0-0 libsdl2-image-2.0-0 libsdl2-mixer-2.0-0 libsdl2-net-2.0-0 libsdl2-ttf-2.0-0
#include <SDL2/SDL_ttf.h>  // sudo apt-get install libsdl2-ttf-dev
//#include <SDL/SDL_gfx.h> // sudo apt-get install libsdl-gfx1.2-5
#include <math.h>

#define PI 3.14159265

#define CALCULATION 0 //0 for CPU; 1 for GPU
#define COLORBITS 32
#define FONT 12
#define WINDOWHEIGHT 2000
#define WINDOWWIDTH 2600
#define LINETHICKNESS 7
#define CIRCLESTEP 0.1


int initWindow(SDL_Window** window, SDL_Renderer** renderer, int iHeight, int iWidth);
int addPoint(SDL_Renderer** renderer, int xPos, int yPos, int color[]);
int addLine(SDL_Renderer** renderer, int x1, int y1, int x2, int y2, int color[]);
int addBlendLine(SDL_Renderer** renderer, int x1, int y1, int x2, int y2, int color[],int blend);
int addRectFill(SDL_Renderer** renderer,  SDL_Rect* rect, int xPos, int yPos, int height, int width, int color[]);
int addRectNoFill(SDL_Renderer** renderer,  SDL_Rect* rect, int xPos, int yPos, int height, int width, int color[]);
int addCircle(SDL_Renderer** renderer, int xPos, int yPos, int radius, int color[]);
int addArrowRight(SDL_Renderer** renderer, int xPos, int yPos, int size, int color[]);
int addArrowDownR(SDL_Renderer** renderer, int xPos, int yPos, int size, int color[]);
int addArrowUpR(SDL_Renderer** renderer, int xPos, int yPos, int size, int color[]);
int addTxt(SDL_Renderer** renderer,SDL_Texture** text, char txt[], int xPos, int yPos, int fontSize, int color[]);
//int loadPicture(char fileName[],SDL_Renderer* renderer, SDL_Texture ** output)
//int addPict(SDL_Renderer** renderer,char fileName[], int xPos, int yPos);
void pause();
int closeWindow(SDL_Window** window, SDL_Renderer** renderer);
void windowMain();




#endif
