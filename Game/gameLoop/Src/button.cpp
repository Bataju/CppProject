#include"button.h"

SDL_Rect Button::srcRect = { 0 ,0, 200, 50 }; //SAME FOR ALL THE BUTTONS

Button::Button()
{
}
void Button::displayButton(const char* path, int xpos, int ypos, int width, int height)
{
    destRect.x = xpos;
    destRect.y = ypos;
    destRect.w = width;
    destRect.h = height;
    SDL_Surface* tempSurface = IMG_Load(path);
    buttonTexture = SDL_CreateTextureFromSurface(dashRenderer, tempSurface);
    SDL_FreeSurface(tempSurface);
    SDL_RenderCopyEx(dashRenderer, buttonTexture, &srcRect, &destRect, NULL, NULL, SDL_FLIP_NONE);
}
