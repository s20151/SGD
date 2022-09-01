#include <SDL.h>
#include <iostream>
#include <SDL_image.h>
#include "../include/RenderWindow.hpp"
#include "../include/Entity.hpp"

RenderWindow::RenderWindow(const char* title, int width, int height)
        :window(NULL), renderer(NULL) {
    window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);

    if (window == NULL)
    {
        std::cout << "Window failed to init. Error: " << SDL_GetError() << std::endl;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

SDL_Texture* RenderWindow::loadTexture(const char* filePath) {
    SDL_Texture* texture = NULL;
    texture = IMG_LoadTexture(renderer, filePath);

    if (texture == NULL)
        std::cout << "Failed to load texture. Error: " << SDL_GetError() << std::endl;

    return texture;
}

void RenderWindow::cleanUp() {
    SDL_DestroyWindow(window);
}

void RenderWindow::clear() {
    SDL_RenderClear(renderer);
}

void RenderWindow::render(Entity& entity) {
    render(entity.getHitbox()->x, entity.getHitbox()->y, entity.getTex());
}

//renderowanie tekstury w pozycji
void RenderWindow::render(double p_x, double p_y, SDL_Texture* texture) {
    SDL_Rect src;
    src.x = 0;
    src.y = 0;
    SDL_QueryTexture(texture, NULL, NULL, &src.w, &src.h);

    SDL_Rect dst;
    dst.x = p_x;
    dst.y = p_y;
    dst.w = src.w/2;
    dst.h = src.h/2;
    SDL_RenderCopy(renderer, texture, &src, &dst);
}
void RenderWindow::display() {
    SDL_RenderPresent(renderer);
}