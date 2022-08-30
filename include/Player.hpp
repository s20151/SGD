#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "Entity.hpp"

class Player : public Entity {

public:
    Player(float p_x, float p_y, SDL_Texture* texture);
    void update(float deltaTime, bool moveLeft, bool moveRight, bool jump, std::vector<Entity> floor,
                std::vector<Entity> spikes);

private:
    float velocityX, velocityY;
    bool onGround;

    void Gravity();

    void Jump();
};