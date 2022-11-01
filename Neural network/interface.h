#ifndef INTERFACE_H
#define INTERFACE_H

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif


#include <stdio.h>
#include <stdlib.h>
//#include <SDL2/SDL.h> // For LINUX: sudo apt install libsdl2-2.0-0 libsdl2-gfx-1.0-0 libsdl2-image-2.0-0 libsdl2-mixer-2.0-0 libsdl2-net-2.0-0 libsdl2-ttf-2.0-0
#include <SDL.h> // For WINDOWS: https://www.matsson.com/prog/sdl2-mingw-w64-tutorial.php
//#include <SDL2/SDL_ttf.h>  //FOR LINUX:  sudo apt-get install libsdl2-ttf-dev
#include <SDL_ttf.h>  // FOR WINDOWS: https://github.com/libsdl-org/SDL_ttf/releases
//#include <SDL/SDL_gfx.h> // sudo apt-get install libsdl-gfx1.2-5
#include <math.h>

#define PI 3.14159265

#define CALCULATION 0 //0 for CPU; 1 for GPU
#define COLORBITS 32
#define FONT 12
#define WINDOWHEIGHT 1000
#define WINDOWWIDTH 1800
#define LINETHICKNESS 5
#define CIRCLESTEP 0.1
#define MAXSTRING 400


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
