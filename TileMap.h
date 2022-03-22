#pragma once
#include <SDL2/SDL.h>
#include <vector>

class TileMap
{
public:
    enum MapType
    {
        Background,
        Passages,
        Walls,
        Decorations,
        Objects
    };

    TileMap();
    ~TileMap();

    void LoadMap(const char* filePath, MapType type, int sizeX, int sizeY, int tileScale);
    void AddTile(std::string tilePath, int x, int y, int scale, int id);
private:
    std::vector<class Entity*> tiles;
};