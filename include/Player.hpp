#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "Entity.hpp"

class Player : public Entity {

public:
    Player(double p_x, double p_y, SDL_Texture* texture);
    void updateMovement(double deltaTime, bool moveLeft, bool moveRight, bool jump, std::vector<Entity> floor,
                std::vector<Entity> spikes);
    bool getJumping();
    bool getStanding();
    void SetJumpTime();
    void Jump();
    void Gravity();

private:
    bool jumping = false;
    bool standing = true;
    double accelerator1 = 0;
    double accelerator2 = 0;
    double lastJump = 0;
    double jumpTimer;
    double jumpHeight = -25;

};