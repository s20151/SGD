#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "Entity.hpp"

class Player : public Entity {

public:
    Player(float p_x, float p_y, SDL_Texture* texture);
    void jump();
    void moveRight();
    void moveLeft();

private:
    float velocityX, velocityY;
    bool onGround;
};