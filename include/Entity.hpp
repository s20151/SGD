#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <vector>

class Entity {
public:
    Entity(double p_x, double p_y, SDL_Texture* texture);
    SDL_Texture* getTex();
    const SDL_Rect * getCurrentFrame();
    void updateCurrentFrame(double p_x, double p_y);

private:
    SDL_Rect currentFrame;
    SDL_Texture* tex;
};
