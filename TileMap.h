#pragma once
#include <SDL2/SDL.h>
#include <vector>

class TileMap
{
public:
    TileMap();
    ~TileMap();

    void LoadMap(const char* path, int sizeX, int sizeY, int tileScale);
    void AddTile(int x, int y, int scale, int id);
private:
    std::vector<class Entity*> tiles;
};