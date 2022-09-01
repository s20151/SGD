#include <SDL.h>
#include <SDL_events.h>
#include <SDL_image.h>
#include <cmath>
#include <vector>
#include <string>
#include <iostream>

#include "../include/Player.hpp"
#include "../include/Entity.hpp"

const double GRAVITY = 2.2;
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 400;

Player::Player(double p_x, double p_y, SDL_Texture* texture)
        : Entity{ p_x, p_y, texture}{
}

double tmp_x;

void Player::update(double deltaTime, bool moveLeft, bool moveRight, bool jump,
                    std::vector<Entity> floor,std::vector<Entity> spikes) {
    if(getCurrentFrame()->x < 0) { updateCurrentFrame(0, getCurrentFrame()->y); }
    if(getCurrentFrame()->x > 775) { updateCurrentFrame(775, getCurrentFrame()->y); }
    tmp_x = getCurrentFrame()->x;
    double decceleration = 0.3;
    if(moveRight){
        tmp_x = getCurrentFrame()->x + 5;
    }

    if(moveLeft){
        tmp_x = getCurrentFrame()->x - 5;
    }

    if(jump && standing) {
        standing = false;
        jumping = true;
        Jump();
    }
    else{
        Gravity();
        if(getCurrentFrame()->y >= 351) {
            updateCurrentFrame(getCurrentFrame()->x, 351);
            standing = true;
        }

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
        if (SDL_HasIntersection(getCurrentFrame(), s.getCurrentFrame())){

            updateCurrentFrame(0,351);

            jumping = false;
        }
    }
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

    GetJumpTime();

    if (getJumping()) {
        accelerator1 = accelerator1 + 0.03;
        accelerator2 = accelerator2 + 0.1;
        jumpHeight = jumpHeight + GRAVITY;
        updateCurrentFrame(tmp_x , getCurrentFrame()->y + GRAVITY + accelerator1 + accelerator2 + jumpHeight);
        if (jumpHeight > 0) {
            jumping = false;
            jumpHeight = -25;
        }
    }
    else {
        accelerator1 = accelerator1 + 0.09;
        accelerator2 = accelerator2 + 0.09;
        updateCurrentFrame(tmp_x , getCurrentFrame()->y + GRAVITY + accelerator1 + accelerator2);
    }
}

void Player::Jump() {
    if (jumpTimer - lastJump > 180) {
        accelerator1 = 0;
        accelerator2 = 0;
        jumping = true;
        lastJump = jumpTimer;
    }
    else {
        Gravity();
    }
}