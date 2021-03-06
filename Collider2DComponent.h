#pragma once
#include <string>
#include <SDL2/SDL.h>
#include "Components.h"

class Collider2DComponent : public Component
{
public: 
    SDL_Rect collider;
    std::string tag;

    TransformComponent* transform;

    Collider2DComponent(const char* tag)
    {
        this->tag = tag;
    }

    void init() override
    {
        if (!entity->hasComponent<TransformComponent>())
        {
            entity->addComponent<TransformComponent>();
        }
        transform = &entity->getComponent<TransformComponent>();

        GameController::colliders.push_back(this);
    }

    void fixedupdate() override
    {
        collider.x = static_cast<int>(transform->position.x);
        collider.y = static_cast<int>(transform->position.y);
        collider.w = transform->width * transform->scale;
        collider.h = transform->height * transform->scale;
    }
};