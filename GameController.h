#ifndef GameController_h
#define GameController_h

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class GameController
{
private:
    int rcounter = 0;
    int fcounter = 0;
    bool isRunning;
    SDL_Window* window;

public:
    GameController();
    ~GameController();
    void init(const char* title, int x, int y, int width, int height, bool fullscreen);

    void HandleEvents();
    void Update();
    void FixedUpdate();
    void Render();
    void Clean();

    bool Running() {return isRunning;}

    static SDL_Renderer* renderer;
    static SDL_Event event;
};
#endif