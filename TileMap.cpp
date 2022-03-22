#include "TileMap.h"
#include "GameController.h"
#include "Components.h"
#include <fstream>

extern Manager manager;

TileMap::TileMap()
{}
TileMap::~TileMap()
{
    tiles.clear();
}

void TileMap::LoadMap(const char* filePath, MapType type, int sizeX, int sizeY, int tileScale)
{
    int tileID;

    std::string tilePath = "";
    switch (type)
    {
    case MapType::Background:
        tilePath = "img/Map_Background/";
        break;
    case MapType::Passages:
        tilePath = "img/Map_Passages/";
        break;
    case MapType::Walls:
        tilePath = "img/Map_Walls/";
        break;
    case MapType::Decorations:
        tilePath = "img/Map_Other/";
        break;
    case MapType::Objects:
        tilePath = "img/Map_Other/";
        break;
    default:
        tilePath = "img/Map_Other/";
        break;
    }

    std::fstream mapFile;
    mapFile.open(filePath);
    for (int y = 0; y < sizeY; y++)
    {
        for (int x = 0; x < sizeX; x++)
        {
            mapFile >> tileID;
            AddTile(tilePath, x * 16 * tileScale, y * 16 * tileScale, tileScale, tileID);
        }
    }
    mapFile.close();
}
void TileMap::AddTile(std::string tilePath, int x, int y, int scale, int id)
{
    auto& tile(manager.addEntity());
    tile.addComponent<TileComponent>(tilePath, x, y, 16, 16, scale, id);
    tile.addGroup(GameController::groupMap);
    tiles.push_back(&tile);
}