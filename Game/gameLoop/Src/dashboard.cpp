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
bool Dashboard::playClicked = false;
bool Dashboard::quitClicked = false;
bool Dashboard::helpClicked = false;
bool Dashboard::isDashRunning = false;

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
    buttonArray = new Button[6];
    buttonArray[0] = Button("gameLoop/gfx/buttonPlay.png", 30, 30, 200, 50);
    buttonArray[1] = Button("gameLoop/gfx/buttonQuit.png", 30, 110, 200, 50);
    buttonArray[2] = Button("gameLoop/gfx/buttonHelp.png", 30, 190, 200, 50);
    for (int i = 0; i < 3; i++)
    {
        buttonArray[i].isSelected = false; // all blue buttons
    }
    buttonArray[3] = Button("gameLoop/gfx/buttonPlay2.png", 30, 30, 200, 50);
    buttonArray[4] = Button("gameLoop/gfx/buttonQuit2.png", 30, 110, 200, 50);
    buttonArray[5] = Button("gameLoop/gfx/buttonHelp2.png", 30, 190, 200, 50);
}

void Dashboard::dashHandleEvents()
{
    SDL_PollEvent(&dashEvent);
    for (int i = 0; i < 3; i++)
    {
        buttonArray[i].handleEvents();
    }
}
void Dashboard::dashUpdate()
{
}
void Dashboard::dashRender()
{
    SDL_RenderClear(dashRenderer);
    SDL_Surface* tempSurface = IMG_Load("gameLoop/gfx/dashboard-min.png");
    dashTexture = SDL_CreateTextureFromSurface(dashRenderer, tempSurface);
    SDL_RenderCopyEx(dashRenderer, dashTexture, &srcRect, &destRect, NULL, NULL, SDL_FLIP_NONE);
    if (buttonArray[0].isSelected == false)
        buttonArray[0].displayButton();
    else
        buttonArray[3].displayButton();
    if (buttonArray[1].isSelected == false)
        buttonArray[1].displayButton();
    else
        buttonArray[4].displayButton();
    if (buttonArray[2].isSelected == false)
        buttonArray[2].displayButton();
    else
        buttonArray[5].displayButton();
    SDL_RenderPresent(dashRenderer);
}

void Dashboard::dashClean()
{
    delete[] buttonArray;
    SDL_DestroyWindow(dashWindow);
    SDL_DestroyRenderer(dashRenderer);
    SDL_Quit();
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
 /*if (SDL_MOUSEMOTION == dashEvent.type)
     {
         int x, y;
         SDL_GetMouseState(&x, &y);
         std::cout << x << " : " << y << std::endl;

         if (x >= destRect.x && x <= destRect.x + destRect.w && y >= destRect.y && y <= destRect.y + destRect.h)
         {
             if (SDL_MOUSEBUTTONDOWN == dashEvent.type)
             {
                 if (SDL_BUTTON_LEFT == dashEvent.button.button)
                 {
                    isSelected = true;
                 }
             }
         }
     }*/

     /*if (dashEvent.type == SDL_KEYUP)
        {
            switch (dashEvent.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                Game::isRunning = false;
                break;
            default:
                break;
            }
        }*/
        /*switch (dashEvent.type)
        {
        case SDL_QUIT:
            isDashRunning = false;
            break;
        default:
            break;
        }*/
