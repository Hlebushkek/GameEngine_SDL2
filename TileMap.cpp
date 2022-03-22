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

void TileMap::LoadMap(const char* path, int sizeX, int sizeY, int tileScale)
{
    int tileID;
    std::fstream mapFile;
    mapFile.open(path);

    for (int y = 0; y < sizeY; y++)
    {
        for (int x = 0; x < sizeX; x++)
        {
            mapFile >> tileID;
            AddTile(x * 16 * tileScale, y * 16 * tileScale, tileScale, tileID);
        }
    }

    mapFile.close();
}
void TileMap::AddTile(int x, int y, int scale, int id)
{
    auto& tile(manager.addEntity());
    tile.addComponent<TileComponent>(x, y, 16, 16, scale, id);
    tile.addGroup(GameController::groupMap);
    tiles.push_back(&tile);
}