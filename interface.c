#include "interface.h"








int initWindow(SDL_Window** window, SDL_Renderer** renderer, int iHeight, int iWidth)
{

	int error = 0;	
	if(SDL_Init(SDL_INIT_VIDEO) != 0)
	{printf("ERROR IN initWindow. Code error %s\n", SDL_GetError()); return 1;}
	

	*window = SDL_CreateWindow("Neural Network training", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, iWidth, iHeight, SDL_WINDOW_SHOWN); 
	if (*window == NULL)
	{printf("ERROR IN initWindow. Code error %s\n", SDL_GetError()); SDL_Quit(); return 2;}
	
	
	*renderer= SDL_CreateRenderer(*window, 0, SDL_RENDERER_SOFTWARE);
	if (*renderer == NULL)
	{printf("ERROR IN initWindow. Code error %s\n", SDL_GetError()); SDL_Quit(); return 3;}
	error = SDL_SetRenderDrawColor(*renderer, 255, 255, 255, 255);
	SDL_RenderClear(*renderer);
	SDL_RenderPresent(*renderer);
	
	if (TTF_Init() < 0){SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] > %s", TTF_GetError()); return EXIT_FAILURE;}
	
	
	if (error!=0){printf("ERROR IN initWindow. Code error %i\n", error);}
	return error;
}



int addPoint(SDL_Renderer** renderer, int xPos, int yPos, int color[])
{
	int error = 0;
	error = SDL_SetRenderDrawColor(*renderer, color[0], color[1], color[2], 255);
	for (int i=0; i<LINETHICKNESS;i++)
	{
		
		SDL_RenderDrawPoint(*renderer, xPos, yPos);
	}
	SDL_RenderPresent(*renderer);
	if (error!=0){printf("ERROR IN addPoint. Code error %i\n", error);}
	return error;
}


int addLine(SDL_Renderer** renderer, int x1, int y1, int x2, int y2, int color[])
{

	int error = 0,i;
	error = SDL_SetRenderDrawColor(*renderer, color[0], color[1], color[2], 255);
	
	if(x1==x2) //case of a line going along y axis
	{
		for (i=0; i<=LINETHICKNESS/4;i++)
		{
		SDL_RenderDrawLine(*renderer, x1+i,y1,x2+i,y2);
		}
		for (i=0; i<=LINETHICKNESS/4;i++)
		{
		SDL_RenderDrawLine(*renderer, x1-i,y1,x2-i,y2);
		}
	}
	if(y1==y2) //case of a line going along x axis
	{
		for (i=0; i<=LINETHICKNESS/3;i++)
		{
		SDL_RenderDrawLine(*renderer, x1,y1+i,x2,y2+i);
		}
		for (i=0; i<=LINETHICKNESS/3;i++)
		{
		SDL_RenderDrawLine(*renderer, x1,y1-i,x2,y2-i);
		}
	}
	else //Lines on all directions
	{
		for (i=0; i<=LINETHICKNESS/2;i++)
		{
			SDL_RenderDrawLine(*renderer, x1,y1+i,x2,y2+i);
		}
		for (i=0; i<=LINETHICKNESS/2;i++)
		{
			SDL_RenderDrawLine(*renderer, x1,y1-i,x2,y2-i);
		}
	}
	SDL_RenderPresent(*renderer);
	if (error!=0){printf("ERROR IN addLine. Code error %i\n", error);}
	return error;
}


int addBlendLine(SDL_Renderer** renderer, int x1, int y1, int x2, int y2, int color[],int blend)
{

	int error = 0,i;
	SDL_SetRenderDrawBlendMode(*renderer, SDL_BLENDMODE_BLEND);
	error = SDL_SetRenderDrawColor(*renderer, color[0], color[1], color[2], blend);
	if(x1==x2) //case of a line going along y axis
	{
		for (i=0; i<=LINETHICKNESS/4;i++)
		{
		SDL_RenderDrawLine(*renderer, x1+i,y1,x2+i,y2);
		}
		for (i=0; i<=LINETHICKNESS/4;i++)
		{
		SDL_RenderDrawLine(*renderer, x1-i,y1,x2-i,y2);
		}
	}
	else
	{
		for (i=0; i<=LINETHICKNESS/2;i++)
		{
			SDL_RenderDrawLine(*renderer, x1,y1+i,x2,y2+i);
		}
		for (i=0; i<=LINETHICKNESS/2;i++)
		{
			SDL_RenderDrawLine(*renderer, x1,y1-i,x2,y2-i);
		}
	}
	SDL_RenderPresent(*renderer);
	if (error!=0){printf("ERROR IN addBlendLine. Code error %i\n", error);}
	return error;
}


int addRectFill(SDL_Renderer** renderer, SDL_Rect* rect, int xPos, int yPos, int height, int width, int color[])
{
	int error = 0;
	error = SDL_SetRenderDrawColor(*renderer, color[0], color[1], color[2], 255);
	rect->x = xPos;
	rect->y = yPos;
	rect->w = width;
	rect->h = height;
	error =  SDL_RenderFillRect(*renderer,rect);
	SDL_RenderPresent(*renderer);
	if (error!=0){printf("ERROR IN addRectFill. Code error %i\n", error);}
	return error;
}


int addRectNoFill(SDL_Renderer** renderer, SDL_Rect* rect, int xPos, int yPos, int height, int width, int color[])
{
	int error = 0;
	error = SDL_SetRenderDrawColor(*renderer, color[0], color[1], color[2], 255);
	for (int i=0; i<LINETHICKNESS;i++)
	{
		rect->x = xPos+i;
		rect->y = yPos+i;
		rect->w = width;
		rect->h = height;
		error =  SDL_RenderDrawRect(*renderer,rect);
	}
	SDL_RenderPresent(*renderer);
	if (error!=0){printf("ERROR IN addRectNoFill. Code error %i\n", error);}
	return error;
}


int addCircle(SDL_Renderer** renderer, int xPos, int yPos, int radius, int color[])
{
	float draw=0;
	int error = 0; 
	int xTemp,yTemp;
	error = SDL_SetRenderDrawColor(*renderer, color[0], color[1], color[2], 255);
	
	for (int i=0; i<LINETHICKNESS;i++)
	{
		radius = radius - i*0.05;
		for(draw=0; draw<360;draw+=CIRCLESTEP)
		{
			xTemp = xPos + radius*cos(draw);
			yTemp = yPos + radius*sin(draw);
			SDL_RenderDrawPoint(*renderer, xTemp, yTemp);
		}
	}
	SDL_RenderPresent(*renderer);
	if (error!=0){printf("ERROR IN addCircle. Code error %i\n", error);}
	return error;

}


int addArrowRight(SDL_Renderer** renderer, int xPos, int yPos, int size, int color[])
{
	int xEnd = xPos+size;
	int yEnd = yPos;
	addLine(renderer, xPos,yPos, xEnd,yEnd, color); //body
	
	addLine(renderer, xEnd,yEnd, xEnd - size/2 ,yEnd - size/1.5, color); //extremities
	addLine(renderer, xEnd,yEnd, xEnd - size/2,yEnd + size/1.5, color);
	return 0;
}


int addArrowUpR(SDL_Renderer** renderer, int xPos, int yPos, int size, int color[])
{
	int xEnd = xPos+size;
	int yEnd = yPos-size;
	addLine(renderer, xPos,yPos, xEnd,yEnd, color); //body
	
	addLine(renderer, xEnd,yEnd, xEnd ,yEnd + size, color); //extremities
	addLine(renderer, xEnd,yEnd, xEnd - size,yEnd , color);
	return 0;
}

int addArrowDownR(SDL_Renderer** renderer, int xPos, int yPos, int size, int color[])
{
	int xEnd = xPos+size;
	int yEnd = yPos+size;
	addLine(renderer, xPos,yPos, xEnd,yEnd, color); //body
	
	addLine(renderer, xEnd,yEnd, xEnd ,yEnd - size, color); //extremities
	addLine(renderer, xEnd,yEnd, xEnd - size,yEnd , color);
	return 0;
}



int addTxt(SDL_Renderer** renderer,SDL_Texture** text, char txt[], int xPos, int yPos, int fontSize, int color[])
{

	SDL_Rect position;
	SDL_Surface* textTemp = NULL;
	TTF_Font* font = NULL;
	SDL_Color sdlColor = {color[0], color[1], color[2], 255};

	font = TTF_OpenFont("rsrc/arial.ttf", fontSize);

	textTemp = TTF_RenderText_Blended(font, txt, sdlColor);	        	
	if (text == NULL){SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] > %s", TTF_GetError());}


	*text = SDL_CreateTextureFromSurface(*renderer, textTemp);
	SDL_QueryTexture(*text, NULL, NULL, &position.w, &position.h);
	position.x = xPos;
	position.y = yPos;
        
	SDL_SetRenderDrawColor(*renderer, color[0], color[1], color[2], 255);
	SDL_RenderCopy(*renderer, *text, NULL, &position);
	SDL_RenderPresent(*renderer);


	SDL_FreeSurface(textTemp);
	TTF_CloseFont(font);
	return 0;
}


/*
int loadPicture(char fileName[],SDL_Renderer* renderer, SDL_Texture ** output)
{
	SDL_Surface* image = SDL_LoadBMP(fileName);
	*output = SDL_CreateTextureFromSurface(*renderer, image);
	SDL_FreeSurface(image);
}

int addPict(SDL_Renderer** renderer, SDL_Texture ** image, int xPos, int yPos)
{
	int error = 0;
	
	SDL_RenderCopy(pRenderer, pTextureImage, nullptr, nullptr); // Affiche ma texture sur touts l'écran

	SDL_RenderPresent(pRenderer);  
	if (error!=0){printf("ERROR IN initWindow. Code error %i\n", error);}
	return error;
}
*/







void pause()
{
    int continuer = 1;
    SDL_Event event;
 
    while (continuer)
    {
	SDL_WaitEvent(&event);
	switch(event.type)
	{
	    case SDL_QUIT:
	        continuer = 0;
            case SDL_KEYDOWN:
            	continuer = 0;
	}
    }
}





int closeWindow(SDL_Window** window, SDL_Renderer** renderer)
{
	TTF_Quit();
	SDL_DestroyRenderer(*renderer);
	SDL_DestroyWindow(*window);
	SDL_Quit();
	
	return 0;
}




void windowMain()
{
	int xPos = 150, yPos = 150, xSize = 180, ySize = 220, radius = 50;
	int color[3] = {0,0,0};
	SDL_Rect rect;
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	SDL_Surface* neuron = NULL;
	SDL_Texture* text = NULL;
	
	neuron = SDL_LoadBMP("rsrc/icon.bmp");
	initWindow(&window,&renderer,WINDOWHEIGHT,WINDOWWIDTH);
	addPoint(&renderer,xPos,yPos,color);
	addRectFill(&renderer,&rect,xPos,yPos,xSize,ySize,color);
	addRectNoFill(&renderer,&rect,xPos+200,yPos+200,xSize,ySize,color);
	addLine(&renderer, xPos+300,yPos+300, xPos+500,yPos+400, color);
	addCircle(&renderer, xPos+600,yPos+600,radius,color);
	addArrowUpR(&renderer,100,100,18,color);
	addTxt(&renderer,&text , "HELLO WORLD", 100,100, 18, color); 
	
	pause();
	
	SDL_DestroyTexture(text);
	closeWindow(&window,&renderer);
}





















