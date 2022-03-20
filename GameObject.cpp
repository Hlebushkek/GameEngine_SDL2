#include "GameObject.h"

GameObject::GameObject(const char* texturesheet, int x, int y)
{
    this->objTexture = IMG_LoadTexture(GameController::renderer, texturesheet);

    this->xpos = x;
    this->ypos = y;
}

void GameObject::Update()
{
    xpos++;
    ypos++;
    
    srcRect.x = 0;
    srcRect.y = 0;
    srcRect.w = 32;
    srcRect.h = 32;

    destRect.x = xpos;
    destRect.y = ypos;
    destRect.w = srcRect.w * 2;
    destRect.h = srcRect.h * 2;
}

void GameObject::Renderer()
{
    SDL_RenderCopy(GameController::renderer, objTexture, &srcRect, &destRect);
}