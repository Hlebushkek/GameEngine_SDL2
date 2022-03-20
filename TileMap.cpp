#include "TileMap.h"

TileMap::TileMap(int arr[mapRow][mapColumn])
{
    name_texture_map.insert(std::pair<const char*, SDL_Texture*>("dirt", IMG_LoadTexture(GameController::renderer, "img/Block1.png")));
    name_texture_map.insert(std::pair<const char*, SDL_Texture*>("stone", IMG_LoadTexture(GameController::renderer, "img/Block1.png")));
    name_texture_map.insert(std::pair<const char*, SDL_Texture*>("water", IMG_LoadTexture(GameController::renderer, "img/Block1.png")));

    LoadMap(arr);

    srcRect.x = srcRect.y = destRect.x = destRect.y = 0;
    srcRect.w = srcRect.h = destRect.w = destRect.h = 32;
}
TileMap::~TileMap()
{
    for (const auto& elem : name_texture_map) {
        SDL_DestroyTexture(elem.second);
    }
    name_texture_map.clear();
}

void TileMap::LoadMap(int arr[mapRow][mapColumn])
{
    for (int row = 0; row < mapRow; row++)
    {
        for (int column = 0; column < mapColumn; column++)
        {
            map[row][column] = arr[row][column];
        }
    }
}

void TileMap::DrawMap()
{
    int type = 0;

    for (int row = 0; row < mapRow; row++)
    {
        for (int column = 0; column < mapColumn; column++)
        {
            type = map[row][column];

            destRect.x = column * 32;
            destRect.y = row * 32;

            switch (type)
            {
            case 0:
                SDL_RenderCopy(GameController::renderer, name_texture_map["dirt"], &srcRect, &destRect);
                break;
            case 1:
                SDL_RenderCopy(GameController::renderer, name_texture_map["stone"], &srcRect, &destRect);
                break;
            case 2:
                SDL_RenderCopy(GameController::renderer, name_texture_map["water"], &srcRect, &destRect);
                break;
            }
        }
    }
}