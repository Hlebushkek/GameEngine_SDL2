//g++ *.cpp -o main -L/usr/local/lib -lSDL2 -lSDL2_image -std=c++17
#define FPS 60
#define FRAME_DELAY (1000 / FPS)

#include "GameController.h"

GameController* gameController = nullptr;

int main(int argc, char *argv[])
{
    Uint32 lastExecTime;

    gameController = new GameController();

    gameController->init("MainWindow", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 640, false);
    while (gameController->Running())
    {    
        if (SDL_GetTicks() - lastExecTime >= FRAME_DELAY)
        {
            gameController->HandleEvents();
            gameController->FixedUpdate();
            gameController->Render();

            lastExecTime = SDL_GetTicks();
        }

        gameController->Update();
    }

    gameController->Clean();

    return 0;
}