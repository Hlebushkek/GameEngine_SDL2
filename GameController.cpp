#include "GameController.h"
#include "TileMap.h"

#include "Components.h"
#include "Vector2D.h"
#include "Collision.h"

TileMap* tileMap;
SDL_Event GameController::event;
SDL_Renderer* GameController::renderer = nullptr;
std::vector<Collider2DComponent*> GameController::colliders;

Manager manager;
auto& newPlayer(manager.addEntity());
auto& wall(manager.addEntity());

GameController::GameController()
{}
GameController::~GameController()
{}

void GameController::init(const char* title, int x, int y, int width, int height, bool fullscreen)
{
    int flags = 0;

    if (fullscreen)
    {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        std::cout << "Subsystem Initialized" << std::endl;

        this->window = SDL_CreateWindow(title, x, y, width, height, flags);
        if (this->window)
        {
            std::cout << "Window created" << std::endl;
        }

        this->renderer = SDL_CreateRenderer(window, -1, 0);
        if (this->renderer)
        {
            SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
            std::cout << "Renderer created" << std::endl;
        }

        tileMap = new TileMap();
        tileMap->LoadMap("/Users/glebsobolevsky/Documents/GameEngine_SDL2/img/Level1_Back.map", TileMap::Background, 50, 40, 3);
        tileMap->LoadMap("/Users/glebsobolevsky/Documents/GameEngine_SDL2/img/Level1_Passages.map", TileMap::Passages, 50, 40, 3);
        tileMap->LoadMap("/Users/glebsobolevsky/Documents/GameEngine_SDL2/img/Level1_Walls.map", TileMap::Walls, 50, 40, 3);

        newPlayer.addComponent<TransformComponent>(120, 120, 21, 48, 3);

        std::vector<std::pair<const char*, Animation>> anims;
        anims.push_back(std::make_pair("Idle", Animation(0, 4, 100)));
        newPlayer.addComponent<SpriteComponent>("img/Player1.png", anims);
        
        newPlayer.addComponent<KeyboardControllerComponent>();
        newPlayer.addComponent<Collider2DComponent>("player");
        newPlayer.addGroup(groupPlayers);

        wall.addComponent<TransformComponent>(300, 300, 128, 32, 1);
        wall.addComponent<SpriteComponent>("img/Block1.png");
        wall.addComponent<Collider2DComponent>("wall");
        wall.addGroup(groupMap);

        isRunning = true;
    } else {isRunning = false;}
}

void GameController::HandleEvents()
{
    SDL_PollEvent(&event);

    switch (event.type)
    {
    case SDL_QUIT:
        isRunning = false;
        break;
    default:
        break;
    }
}
void GameController::Update()
{
    //this->rcounter++;
    //std::cout << "rcounter: " << this->rcounter << std::endl;
    manager.update();
}
void GameController::FixedUpdate()
{
    //this->fcounter++;
    //std::cout << "fcounter: " << this->fcounter << std::endl;

    manager.refresh();
    manager.fixedupdate();

    for (auto cc : colliders)
    {
        Collision::AABB(newPlayer.getComponent<Collider2DComponent>(), *cc);
    }
}

auto& tiles(manager.getGroup(GameController::groupMap));
auto& players(manager.getGroup(GameController::groupPlayers));
auto& enemies(manager.getGroup(GameController::groupEnemies));

void GameController::Render()
{
    SDL_RenderClear(renderer);
    
    for (auto& t : tiles) t->draw();
    for (auto& p : players) p->draw();
    for (auto& e : enemies) e->draw();

    SDL_RenderPresent(renderer);
}
void GameController::Clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);

    SDL_Quit();
    std::cout << "Quit game" << std::endl;
}