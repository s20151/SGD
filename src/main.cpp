#include <SDL.h>
#include <SDL_image.h>
#include "../include/RenderWindow.hpp"
#include <iostream>

int main(int argc, char* args[]) {

    if (SDL_Init(SDL_INIT_VIDEO) > 0)
        std::cout << "HEY.. SDL_Init HAS FAILED. SDL_ERROR: " << SDL_GetError() << std::endl;

    if (!(IMG_Init(IMG_INIT_PNG)))
        std::cout << "IMG_init has failed. Error: " << SDL_GetError() << std::endl;

    RenderWindow window("Skaczacy kloc", 640, 320);

    SDL_Texture* grassTexture = window.loadTexture("data/floor.png");

    bool gameRunning = true;

    SDL_Event event;

    while (gameRunning)
    {
        // Get our controls and events
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                gameRunning = false;
        }
        window.clear();
        window.render(grassTexture);
        window.display();
    }

    window.cleanUp();
    SDL_Quit();

    return 0;
}