#pragma once
#include <SDL2/SDL.h>
#include <cstring>
#include "Components.h"

class TileComponent : public Component
{
public:
    TransformComponent* transform;
    SpriteComponent* sprite;

    SDL_Rect tileRect;
    int scale;
    std::string tileID;
    std::string path;

    TileComponent() = default;
    TileComponent(int x, int y, int w, int h, int sc, int id)
    {
        tileRect.x = x;
        tileRect.y = y;
        tileRect.w = w * sc;
        tileRect.h = h * sc;
        scale = sc;
        tileID = id;

        path = "img/tile" + std::to_string(id) + ".png";
    }

    void init() override
    {
        entity->addComponent<TransformComponent>(tileRect.x, tileRect.y, tileRect.w, tileRect.h, scale);
        transform = &entity->getComponent<TransformComponent>();

        entity->addComponent<SpriteComponent>(path.c_str());
        sprite = &entity->getComponent<SpriteComponent>();
    }
};