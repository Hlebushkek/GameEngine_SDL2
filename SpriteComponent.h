#pragma once
#include "SDL2/SDL.h"
#include "GameController.h"
#include "Components.h"
#include "Animation.h"
#include <map>

class SpriteComponent : public Component
{
private:
    TransformComponent* transform;
    SDL_Texture* texture;
    SDL_Rect srcRect, destRect;

    bool animated = false;
    int frames = 0;
    int speed = 100;

public:

    int animIndex = 0;

    std::map<const char*, Animation> animations;

    SpriteComponent() = default;
    SpriteComponent(const char* path)
    {
        setTexture(path);
    }
    SpriteComponent(const char* path, std::vector<std::pair<const char*, Animation>> anims)
    {
        animated = true;

        for (auto &anim: anims)
        {
            animations.emplace(anim);
        }
        Play(animations.begin()->first);

        setTexture(path);
    }
    ~SpriteComponent()
    {
        SDL_DestroyTexture(texture);
    }

    void setTexture(const char* path)
    {
        texture = IMG_LoadTexture(GameController::renderer, path);
    }

    void init() override
    {
        transform = &entity->getComponent<TransformComponent>();

        srcRect.x = srcRect.y = 0;
        srcRect.w = transform->width;
        srcRect.h = transform->height;
        
    }

    void fixedupdate() override
    {
        if (animated)
        {
            srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / speed) % frames);
        }
        srcRect.y = animIndex * transform->height;

        destRect.x = static_cast<int>(transform->position.x);
        destRect.y = static_cast<int>(transform->position.y);
        destRect.w = transform->width * transform->scale;
        destRect.h = transform->height * transform->scale;
    }

    void draw() override
    {
        SDL_RenderCopy(GameController::renderer, texture, &srcRect, &destRect);
    }

    void Play(const char* animName)
    {
        frames = animations[animName].frames;
        animIndex = animations[animName].index;
        speed = animations[animName].speed;
    }
};