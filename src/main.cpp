#include <SDL2/SDL.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_image.h>
#include "../include/RenderWindow.hpp"
#include "../include/Entity.hpp"
#include <iostream>
#include <vector>

int main(int argc, char* args[]) {

    if (SDL_Init(SDL_INIT_VIDEO) > 0)
        std::cout << "HEY.. SDL_Init HAS FAILED. SDL_ERROR: " << SDL_GetError() << std::endl;

    if (!(IMG_Init(IMG_INIT_PNG)))
        std::cout << "IMG_init has failed. Error: " << SDL_GetError() << std::endl;

    RenderWindow window("Skaczacy kloc", 800, 400);

    SDL_Texture* grassTexture = window.loadTexture("data/grass.jpg");
    SDL_Texture* playerTexture = window.loadTexture("data/player.png");
    SDL_Texture* spikeTexture = window.loadTexture("data/spike.png");
    SDL_Texture* winTexture = window.loadTexture("data/win.png");
    SDL_Texture* skyTexture = window.loadTexture("data/sky.png");
    SDL_Texture* castleTexture = window.loadTexture("data/castle.png");


    std::vector<Entity> floor_entities;
    Entity player = Entity(0,351,playerTexture);

    Entity win = Entity(250, 200, winTexture);

    for(int i = 0; i < 801; i+=25){
        floor_entities.push_back(Entity(i,375, grassTexture));
    }
    std::vector<Entity> spike_entities ={
            Entity(100, 350, spikeTexture),
            Entity(125, 350, spikeTexture),
            Entity(150, 350, spikeTexture),
            Entity(225, 350, spikeTexture),
            Entity(350, 350, spikeTexture),
            Entity(375, 350, spikeTexture),
            Entity(450, 350, spikeTexture),
            Entity(525, 350, spikeTexture),
            Entity(550, 350, spikeTexture),
            Entity(575, 350, spikeTexture),
            Entity(650, 350, spikeTexture),
            Entity(675, 350, spikeTexture)
    };

    bool gameRunning = true;

    SDL_Event event;

    while (gameRunning) {
        // Get our controls and events
        if (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                gameRunning = false;
            if (event.type == SDL_KEYDOWN){
                if(event.key.keysym.sym == SDLK_RIGHT && player.getX() < 777){
                    player.setX(player.getX()+3);
                    player.updateCurrentFrame(player.getX()-25, player.getY()-25);
                }
                if(event.key.keysym.sym == SDLK_LEFT && player.getX() > 0){
                    player.setX(player.getX()-3);
                    player.updateCurrentFrame(player.getX()-25, player.getY()-25);
                }
                if(event.key.keysym.sym == SDLK_SPACE){
                    player.jump();
                    player.updateCurrentFrame(player.getX()-25, player.getY()-25);
                }
            }
        }
        window.render(0,0, skyTexture);
        window.render(725,200, castleTexture);

        for (Entity& floor : floor_entities){
            if(SDL_HasIntersection(player.getCurrentFrame(), floor.getCurrentFrame())){
                player.setJumping(false);
                player.setFalling(true);
                player.setJumpspeed(-20);
            }
            window.render(floor);
        }
        for (Entity& spike : spike_entities){
            if(SDL_HasIntersection(player.getCurrentFrame(), spike.getCurrentFrame())){
                player.setX(0);
                player.setY(350);
            }
            window.render(spike);
        }
        window.render(player);
        if(player.getX() > 730){
            window.render(win);
        }
        window.display();
    }

    window.cleanUp();
    SDL_Quit();

    return 0;
}
