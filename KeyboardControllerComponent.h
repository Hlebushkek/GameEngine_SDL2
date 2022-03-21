#pragma once

#include "GameController.h"
#include "ECS.h"
#include "Components.h"

class KeyboardControllerComponent : public Component
{
public:
    TransformComponent* transform;

    void init() override
    {
        transform = &entity->getComponent<TransformComponent>();
    }
    void fixedupdate() override
    {
        if (GameController::event.type == SDL_KEYDOWN /*&& GameController::event.key.repeat == 0*/)
        {
            //std::cout << "KeyDown : " << GameController::event.key.keysym.sym << std::endl;
            switch (GameController::event.key.keysym.sym)
            {
            case SDLK_w:
                transform->velocity.y = -1;
                break;
            case SDLK_s:
                transform->velocity.y = 1;
                break;
            case SDLK_a:
                transform->velocity.x = -1;
                break;
            case SDLK_d:
                transform->velocity.x = 1;
                break;
            default:
                break;
            }
        }

        if (GameController::event.type == SDL_KEYUP)
        {
            //std::cout << "KeyUP : " << GameController::event.key.keysym.sym << std::endl;
            switch (GameController::event.key.keysym.sym)
            {
            case SDLK_w:
                transform->velocity.y = 0;
                break;
            case SDLK_s:
                transform->velocity.y = 0;
                break;
            case SDLK_a:
                transform->velocity.x = 0;
                break;
            case SDLK_d:
                transform->velocity.x = 0;
                break;
            default:
                break;
            }
        }
    }
private:

};
