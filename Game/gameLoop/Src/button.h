#pragma once
#include "SDL.h"
#include <string>
#include "dashboard.h"

class Button :public Dashboard
{
public:
    SDL_Texture* buttonTexture;
    static SDL_Rect srcRect;
    //static SDL_Renderer* buttonRenderer;
    SDL_Rect destRect;
    bool isSelected;
    Button();
    void displayButton(const char* path, int xpos, int ypos, int width, int height);
    bool returnIsSelected() { return isSelected; }
};