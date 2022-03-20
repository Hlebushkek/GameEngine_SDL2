#pragma once
#include "Components.h"
#include "Vector2D.h"

class TransformComponent : public Component
{
public:
    Vector2D position;
    Vector2D velocity;

    int height = 32;
    int width = 32;
    int scale = 1;

    int speed = 3;

    TransformComponent()
    {
        position.Zero();
    }
    TransformComponent(float x, float y)
    {
        setPosition(x, y);
    }
    TransformComponent(float x, float y, int w, int h, int scale)
    {
        setPosition(x, y);
        width = w;
        height = h;
        scale = scale;
    }
    TransformComponent(Vector2D pos)
    {
        position = pos;
    }

    void init() override
    {
        velocity.Zero();
    }
    void fixedupdate() override
    {
        float velocityLength = velocity.length();
        
        if (velocityLength > 0)
        {
            position.x += velocity.x / velocityLength * speed;
            position.y += velocity.y / velocityLength * speed;
        }

        //std::cout << "velocity: " << velocity << std::endl;
        //std::cout << "velocityLength: " << velocityLength << std::endl;
        //std::cout << "pos: " << position <<std::endl;
    }
    void setPosition(float x, float y)
    {
        position.x = x;
        position.y = y;
    }
};