#pragma once
#include <SDL.h>
#include "Entity.hpp"

class RenderWindow {

public:
    RenderWindow(const char* title, int width, int height);
    SDL_Texture* loadTexture(const char* filePath);
    void cleanUp();
    void render(Entity& entity);
    void render(double p_x, double p_y, SDL_Texture *texture);
    void display();
    void clear();
private:
    SDL_Window* window;
    SDL_Renderer* renderer;


};