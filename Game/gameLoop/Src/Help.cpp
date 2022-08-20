#include "dashboard.h"
#include"textureManager.h"
#include<cstdlib>
#include "Help.h"

SDL_Renderer* Help::helpRenderer = nullptr;
SDL_Event Help::helpEvent;

SDL_Texture* Help::helpTexture = nullptr;
SDL_Rect srchelp = { 0, 0, 500, 500 };
SDL_Rect desthelp = { 0, 0, 500, 500 };

Help::Help(){}
Help::~Help(){}

void Help::helpInit(const char* title, int width, int height, bool fullscreen)
{
	int flags = 0;

	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		helpWindow = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
		helpRenderer = SDL_CreateRenderer(helpWindow, -1, 0);
		if (helpRenderer)
		{
			SDL_SetRenderDrawColor(helpRenderer, 0, 0, 0, 0);
		}

		ishelpRunning = true;
	}
	SDL_ShowCursor(true);
}

void Help::helpHandleEvents()
{
	SDL_PollEvent(&helpEvent);

	switch (helpEvent.type)
	{
	case SDL_QUIT:
		ishelpRunning = false;
		std::cout << "yoyo" << std::endl;
		break;
	default:
		break;
	}
}


void Help::helpRender()
{
	SDL_RenderClear(helpRenderer);
	SDL_Surface* temphelp = IMG_Load("gameLoop/gfx/help.png");
	helpTexture = SDL_CreateTextureFromSurface(helpRenderer, temphelp);
	SDL_RenderCopyEx(helpRenderer, helpTexture, &srchelp, &desthelp, NULL, NULL, SDL_FLIP_NONE);
	SDL_RenderPresent(helpRenderer);
}

void Help::helpClean()
{
	SDL_DestroyWindow(helpWindow);
	SDL_DestroyRenderer(helpRenderer);
	SDL_Quit();
}