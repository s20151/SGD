#include <SDL.h>
#include <SDL_events.h>
#include <SDL_image.h>
#include <cmath>
#include <vector>
#include <string>

#include "../include/Player.hpp"
#include "../include/Entity.hpp"

const double GRAVITY = 2;
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 400;

Player::Player(double p_x, double p_y, SDL_Texture* texture)
        : Entity{ p_x, p_y, texture}, xVel(0), yVel(0) {
}

void Player::update(double deltaTime, bool moveLeft, bool moveRight, bool jump,
                    std::vector<Entity> floor,std::vector<Entity> spikes) {
    if(getCurrentFrame()->x < 0) { updateCurrentFrame(0, getCurrentFrame()->y); }
    if(getCurrentFrame()->y > 351) { updateCurrentFrame(getCurrentFrame()->x, 351); }

    if(moveRight){
        updateCurrentFrame((getCurrentFrame()->x + 1 * (double)deltaTime), getCurrentFrame()->y);
    }

    if(moveLeft){
        updateCurrentFrame((getCurrentFrame()->x - 1 * (double)deltaTime), getCurrentFrame()->y);
    }

    if(jump) {
        jumping = true;
        Jump();
    }
    else if(standing){
        Gravity();
    }
    // after touching floor disable gravity/jump
    for (Entity f: floor) {
        if(SDL_HasIntersection(getCurrentFrame(), f.getCurrentFrame())){
            standing = true;
            updateCurrentFrame(getCurrentFrame()->x, 351);
        }
    }
    // after touching spike kill and return to spawn
    for (Entity s: spikes) {
        SDL_Rect temp_rect = {temp_rect.x = getCurrentFrame()->x-25, temp_rect.y = getCurrentFrame()->y-25, temp_rect.w = 50, temp_rect.h = 50};
        if (SDL_HasIntersection(&temp_rect, s.getCurrentFrame())){

            updateCurrentFrame(0,351);

            jumping = false;
        }
    }
}

void Player::setAccelerating(bool new_accelerating) {
    jumping = new_accelerating;
}

bool Player::setJumping(bool new_jumping) {
    jumping = new_jumping;
}

bool Player::getJumping() {
    return jumping;
}

bool Player::getStanding() {
    return standing;
}

void Player::GetJumpTime() {
    jumpTimer = SDL_GetTicks();
}

void Player::Gravity() {
    if (getJumping()) {
        accelerator1 = accelerator1 + 0.001;
        accelerator2 = accelerator2 + 0.001;
        jumpHeight = jumpHeight + GRAVITY;
        updateCurrentFrame(getCurrentFrame()->x , getCurrentFrame()->y + GRAVITY + accelerator1 + accelerator2 + jumpHeight);
        if (jumpHeight > 0) {
            jumping = false;
            jumpHeight = -30;
        }
    }
    else {
        accelerator1 = accelerator1 + 0.005;
        accelerator2 = accelerator2 + 0.004;
        updateCurrentFrame(getCurrentFrame()->x , getCurrentFrame()->y + GRAVITY + accelerator1 + accelerator2);
    }
}

void Player::Jump() {
    if (jumpTimer - lastJump > 360)
    {
        accelerator1 = 0;
        accelerator2 = 0;
        jumping = true;
        lastJump = jumpTimer;
    }
    else {
        Gravity();
    }
}