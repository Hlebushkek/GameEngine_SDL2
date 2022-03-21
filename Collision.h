#pragma once
#include <SDL2/SDL.h>

class Collision
{
public:
    static bool AABB(const SDL_Rect& rectA, const SDL_Rect& rectB);
    static bool AABB(const class Collider2DComponent& cA, const Collider2DComponent& cB);
};