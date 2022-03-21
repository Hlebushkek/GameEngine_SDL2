#include "Collision.h"
#include "Collider2DComponent.h"

bool Collision::AABB(const SDL_Rect& rectA, const SDL_Rect& rectB)
{
    if (
        rectA.x + rectA.w >= rectB.x &&
        rectB.x + rectB.w >= rectA.x &&
        rectA.y + rectA.h >= rectB.y &&
        rectB.y + rectB.h >= rectA.y
        )
    {
        return true;
    }

    return false;
}

bool Collision::AABB(const class Collider2DComponent& cA, const Collider2DComponent& cB)
{
    if (AABB(cA.collider, cB.collider))
    {
        //std::cout << cA.tag << "hit " << cB.tag << std::endl;
        return true;
    }
    return false;
}