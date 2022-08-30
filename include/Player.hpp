#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "Entity.hpp"

class Player : public Entity {

public:
    Player(float p_x, float p_y, SDL_Texture* texture);
    void moveRight();
    void moveLeft();

private:
    float velocityX, velocityY;
    bool onGround;

    void update(double deltaTime, bool moveLeft, bool moveRight, bool jump, std::vector<Entity> floor,
                std::vector<Entity> spikes);
};