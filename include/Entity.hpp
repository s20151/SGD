#pragma once
#include <SDL.h>
#include <SDL_image.h>

class Entity {
public:
    Entity(float p_x, float p_y, SDL_Texture* texture);
    float getX();
    float getY();
    void setX(float p_x);
    void setY(float p_y);
    SDL_Texture* getTex();
    const SDL_Rect * getCurrentFrame();
    void updateCurrentFrame(float p_x, float p_y);
private:
    float x, y;
    SDL_Rect currentFrame;
    SDL_Texture* tex;
};