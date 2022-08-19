#include "dashboard.h"
#include"textureManager.h"
#include"Button.h"
#include<cstdlib>

SDL_Renderer* Dashboard::dashRenderer = nullptr;            //we can reassign
SDL_Event Dashboard::dashEvent;
SDL_Texture* Dashboard::dashTexture = nullptr;
SDL_Rect srcRect = { 0, 0, 800, 640 };
SDL_Rect destRect = { 0, 0, 800, 640 };
Button* buttonArray;

Dashboard::Dashboard()
{}
Dashboard::~Dashboard()
{}
void Dashboard::dashInit(const char* title, int width, int height, bool fullscreen)
{
    int flags = 0;
    if (fullscreen)
    {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        dashWindow = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
        dashRenderer = SDL_CreateRenderer(dashWindow, -1, 0);
        if (dashRenderer)
        {
            SDL_SetRenderDrawColor(dashRenderer, 0, 0, 0, 0);
        }

        isDashRunning = true;
    }
}

void Dashboard::dashHandleEvents()
{
    SDL_PollEvent(&dashEvent);
    if (SDL_MOUSEMOTION == dashEvent.type)
    {
        int x, y;
        SDL_GetMouseState(&x, &y);
        std::cout << x << " : " << y << std::endl;
    }
    /*if (SDL_MOUSEBUTTONDOWN == dashEvent.type)
    {
        if (SDL_BUTTON_LEFT == dashEvent.button.button)
        {
            std::cout << "left mouse button down" << std::endl;
        }
        if (SDL_BUTTON_RIGHT == dashEvent.button.button)
        {
            std::cout << "right mouse button down" << std::endl;
        }
        if (SDL_BUTTON_MIDDLE == dashEvent.button.button)
        {
            std::cout << "middle mouse button down" << std::endl;
        }
    }
    if (SDL_MOUSEBUTTONUP == dashEvent.type)
    {
        if (SDL_BUTTON_LEFT == dashEvent.button.button)
        {
            std::cout << "left mouse button UP" << std::endl;
        }
        if (SDL_BUTTON_RIGHT == dashEvent.button.button)
        {
            std::cout << "right mouse button UP" << std::endl;
        }
        if (SDL_BUTTON_MIDDLE == dashEvent.button.button)
        {
            std::cout << "middle mouse button UP" << std::endl;
        }
    }*/
    switch (dashEvent.type)
    {
    case SDL_QUIT:
        isDashRunning = false;
        break;
    default:
        break;
    }
}
void Dashboard::dashUpdate()
{
    buttonArray = new Button[6];//dynamically
    buttonArray[0].displayButton("gameLoop/gfx/playButton.png", 30, 30, 200, 50);
    buttonArray[1].displayButton("gameLoop/gfx/quitButton.png", 30, 110, 200, 50);
    buttonArray[2].displayButton("gameLoop/gfx/helpButton.png", 30, 190, 200, 50);
    SDL_RenderPresent(dashRenderer);
    //buttonArray[3] = Button("Play", "gameLoop/gfx/playUpdated.png", 30, 30, 200, 50);
   // buttonArray[4] = Button("Quit", "gameLoop/gfx/quitUpdated.png", 110, 110, 200, 50);
   // buttonArray[5] = Button("Help", "gameLoop/gfx/helpUpdated.png", 190, 190, 200, 50);
}
void Dashboard::dashRender()
{
    SDL_RenderClear(dashRenderer);
    SDL_Surface* tempSurface = IMG_Load("gameLoop/gfx/dashboard-min.png");
    dashTexture = SDL_CreateTextureFromSurface(dashRenderer, tempSurface);
    SDL_FreeSurface(tempSurface);
    SDL_RenderCopyEx(dashRenderer, dashTexture, &srcRect, &destRect, NULL, NULL, SDL_FLIP_NONE);
}

void Dashboard::dashClean()
{
    delete[] buttonArray;
    SDL_DestroyWindow(dashWindow);
    SDL_DestroyRenderer(dashRenderer);
    SDL_Quit();
}

