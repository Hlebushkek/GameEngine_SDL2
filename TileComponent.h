#pragma once
#include <SDL2/SDL.h>
#include <cstring>
#include "Components.h"

class TileComponent : public Component
{
public:
    TransformComponent* transform;
    SDL_Texture* texture;
    SDL_Rect srcRect, destRect;

    int scale;
    std::string tileID;
    std::string path;

    TileComponent() = default;
    TileComponent(std::string p, int x, int y, int w, int h, int sc, int id)
    {
        srcRect.x = srcRect.y = 0;
        srcRect.w = w;
        srcRect.h = h;
        scale = sc;
        tileID = id;

        destRect.x = x;
        destRect.y = y;
        destRect.w = w * sc;
        destRect.h = h * sc;
        
        path = p;
        path += "tile";
        path += std::to_string(id);
        path += ".png";
        
        texture = IMG_LoadTexture(GameController::renderer, path.c_str());
    }
    ~TileComponent()
    {
        SDL_DestroyTexture(texture);
    }

    void draw() override
    {
        SDL_RenderCopy(GameController::renderer, texture, &srcRect, &destRect);
    }
};