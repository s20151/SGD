#include <SDL.h>
#include <SDL_rect.h>
#include <SDL_image.h>
#include "../include/RenderWindow.hpp"
#include "../include/Player.hpp"
#include <iostream>
#include <vector>


bool init() {
    if (SDL_Init(SDL_INIT_VIDEO) > 0)
        std::cout << "HEY.. SDL_Init HAS FAILED. SDL_ERROR: " << SDL_GetError() << std::endl;

    if (!(IMG_Init(IMG_INIT_PNG)))
        std::cout << "IMG_init has failed. Error: " << SDL_GetError() << std::endl;
    return true;
}

bool SDLinit = init();

RenderWindow window("Skaczacy kloc", 800, 400);

SDL_Texture *grassTexture = window.loadTexture("data/grass.jpg");
SDL_Texture *playerTexture = window.loadTexture("data/player.png");
SDL_Texture *spikeTexture = window.loadTexture("data/spike.png");
SDL_Texture *winTexture = window.loadTexture("data/win.png");
SDL_Texture *skyTexture = window.loadTexture("data/sky.png");
SDL_Texture *castleTexture = window.loadTexture("data/castle.png");

std::vector<Entity> loadFloor() {
    std::vector<Entity> floor_entities = {};
    for (int i = 0; i < 801; i += 25) {
        floor_entities.push_back(Entity(i, 375, grassTexture));
    }
    floor_entities.push_back(Entity(275, 350, grassTexture));
    floor_entities.push_back(Entity(300, 350, grassTexture));
    floor_entities.push_back(Entity(325, 350, grassTexture));
    return floor_entities;
}

std::vector<Entity> loadSikes() {
    std::vector<Entity> spike_entities = {
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
            Entity(675, 350, spikeTexture),
            Entity(300, 325, spikeTexture),
            Entity(250, 350, spikeTexture)
    };
    return spike_entities;
}

std::vector<Entity> floor = loadFloor();
std::vector<Entity> spikes = loadSikes();
Player player = Player(0, 351, playerTexture);
Entity win = Entity(250, 200, winTexture);

bool gameRunning = true;
SDL_Event event;

Uint64 NOW = SDL_GetPerformanceCounter();
Uint64 LAST = 0;

double deltaTime = 0;

bool moveRight = false;
bool moveLeft = false;
bool jump = false;


bool playerWon = false;

void Event() {
    SDL_PollEvent(&event);
    if (event.type == SDL_QUIT) {
        gameRunning = false;
    }
    if (event.type == SDL_KEYDOWN) {
        if (event.key.keysym.sym == SDLK_RIGHT) {
            moveRight = true;
        }
        if (event.key.keysym.sym == SDLK_LEFT) {
            moveLeft = true;
        }
        if (event.key.keysym.sym == SDLK_SPACE) {
            jump = true;
        }
    } else if (event.type == SDL_KEYUP) {
        if (event.key.keysym.sym == SDLK_RIGHT) {
            moveRight = false;
            player.setAcceleration(0);
        }
        if (event.key.keysym.sym == SDLK_LEFT) {
            moveLeft = false;
            player.setAcceleration(0);
        }
        if (event.key.keysym.sym == SDLK_SPACE) {
            jump = false;
        }
    }
}


void Update() {
    player.SetDeltaTime();
    LAST = NOW;
    NOW = SDL_GetPerformanceCounter();
    deltaTime = (double)((NOW - LAST)*1000 / (double)SDL_GetPerformanceFrequency() );
//    std::cout << player.getHitbox()->x;
//    std::cout << " ";
//    std::cout << player.getHitbox()->y << std::endl;
//    std::cout << "delta time: ";
//    std::cout << deltaTime << std::endl;
    if (player.getHitbox()->x > 725) playerWon = true;
    if (!playerWon) {
        player.updateMovement(deltaTime, moveLeft, moveRight, jump, floor, spikes);
    }
}

void Graphics() {
    window.clear();
    window.render(0, 0, skyTexture);
    window.render(725, 200, castleTexture);
    window.render(player);
    for (Entity f: floor) {
        window.render(f);
    }
    for (Entity s: spikes) {
        window.render(s);
    }
    if (playerWon) {
        window.render(win);
    }
    window.display();
}

void Game() {
    Update();
    Event();
    Graphics();
}

int main(int argc, char *args[]) {

    const int FPS = 60;
    const int frameDelay = 1000 / FPS;
    Uint32 frameStart;
    int frameTime;

    while (gameRunning) {

        frameStart = SDL_GetTicks();
        Game();
        frameTime = SDL_GetTicks() - frameStart;

        if (frameDelay > frameTime) SDL_Delay(frameDelay - frameTime);
    }
    window.cleanUp();
    SDL_Quit();

    return 0;
}
