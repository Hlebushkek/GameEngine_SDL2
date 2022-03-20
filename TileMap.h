#pragma once
#include "GameController.h"
#include <map>

#define mapRow 20
#define mapColumn 25

class TileMap
{
public:
    TileMap(int arr[mapRow][mapColumn]);
    ~TileMap();

    void LoadMap(int arr[mapRow][mapColumn]);
    void DrawMap();

private:
    SDL_Rect srcRect, destRect;

    std::map<const char*, SDL_Texture*> name_texture_map;
    int map[mapRow][mapColumn];
};