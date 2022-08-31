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
    bool jumping = false;
    bool accelerating = false;
    void Gravity();
    void Jump();
    float xVel, yVel;

    bool getJumping();
    bool getAccelerating();

    void setAccelerating(bool new_accelerating);
    bool setJumping(bool new_jumping);

    void Gravity(float deltaTime);
};