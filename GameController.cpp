#include "GameController.h"
#include "TileMap.h"

#include "Components.h"
#include "Vector2D.h"
#include "Collision.h"

int arr[20][25] =
{
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 }
};
TileMap* tileMap;
SDL_Event GameController::event;
SDL_Renderer* GameController::renderer = nullptr;

Manager manager;
auto& newPlayer(manager.addEntity());
auto& wall(manager.addEntity());


GameController::GameController(){}
GameController::~GameController(){}

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

        tileMap = new TileMap(arr);

        newPlayer.addComponent<TransformComponent>(120, 120);
        newPlayer.addComponent<SpriteComponent>("img/Block1.png");
        newPlayer.addComponent<KeyboardControllerComponent>();
        newPlayer.addComponent<Collider2DComponent>("player");

        wall.addComponent<TransformComponent>(300, 300, 128, 32, 1);
        wall.addComponent<SpriteComponent>("img/Block1.png");
        wall.addComponent<Collider2DComponent>("wall");

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

    if (Collision::AABB(newPlayer.getComponent<Collider2DComponent>().collider, wall.getComponent<Collider2DComponent>().collider))
    {
        newPlayer.getComponent<TransformComponent>().velocity * -1;
        std::cout << "Player overlap wall" << std::endl;
    }
}

void GameController::Render()
{
    SDL_RenderClear(renderer);
    //to render
    tileMap->DrawMap();
    manager.draw();
    //
    SDL_RenderPresent(renderer);
}
void GameController::Clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);

    SDL_Quit();
    std::cout << "Quit game" << std::endl;
}