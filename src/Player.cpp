#include <SDL.h>
#include <SDL_events.h>
#include <vector>
#include "../include/Player.hpp"
#include <cmath>

const double GRAVITY = 10;
double tmp_x;

Player::Player(double p_x, double p_y, SDL_Texture *texture)
        : Entity{p_x, p_y, texture} {
}

void Player::updateMovement(double deltaTime, bool moveLeft, bool moveRight, bool jump,
                    std::vector<Entity> floor, std::vector<Entity> spikes) {
    if (getHitbox()->x < 0) { updateHitboxPos(0, getHitbox()->y); }
    if (getHitbox()->x > 775) { updateHitboxPos(775, getHitbox()->y); }
    tmp_x = getHitbox()->x;
    double decceleration = 0.3;
    if (moveRight) {
        tmp_x = getHitbox()->x + 5;
    }

    if (moveLeft) {
        tmp_x = getHitbox()->x - 5;
    }

    if (jump && standing) {
        standing = false;
        jumping = true;
        Jump();
    } else {
        Gravity();
        if (getHitbox()->y >= 351) {
//            accelerator1 = 0;
//            accelerator2 = 0;
            standing = true;
        }
    }
    // after touching floor disable gravity/jump
    for (Entity f: floor) {
        if (SDL_HasIntersection(getHitbox(), f.getHitbox())) {
            if(f.getHitbox()->y > getHitbox()->y){
                standing = true;
                updateHitboxPos(getHitbox()->x, f.getHitbox()->y-25);
            } else if(f.getHitbox()->y < getHitbox()->y){
                updateHitboxPos(getHitbox()->x, f.getHitbox()->y+25);
            } else if (f.getHitbox()->x > getHitbox()->x){
                updateHitboxPos(getHitbox()->x-25, f.getHitbox()->y);
            } else if (f.getHitbox()->x < getHitbox()->x){
                updateHitboxPos(getHitbox()->x+25, f.getHitbox()->y);
            }
        }
    }
    // after touching spike kill and return to spawn
    for (Entity s: spikes) {
        if (SDL_HasIntersection(getHitbox(), s.getHitbox())) {

            updateHitboxPos(0, 351);

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

void Player::SetJumpTime() { // pdt
    jumpTimer = deltaTimer;
}

void Player::SetGravityTime() { //fdt
    gravityTimer = (deltaTimer - jumpTimer)/1000;
}

void Player::SetDeltaTime() { //dt
    deltaTimer = SDL_GetTicks();
}

void Player::Gravity() {

    SetGravityTime();
    double newY;
    if (getJumping()) {
        double tmp_dest = getHitbox()->y;
//        accelerator1 = accelerator1 + 0.03;
//        accelerator2 = accelerator2 + 0.1;
//        jumpHeight = jumpHeight + GRAVITY;
        newY = getHitbox()->y + jumpHeight * gravityTimer + 5 * pow(gravityTimer, 2) * GRAVITY - 3;
        updateHitboxPos(tmp_x,  newY);
        if (tmp_dest < newY) {
            jumping = false;
            SetJumpTime();
//            jumpHeight = -25;
        }
    } else {
//        accelerator1 = accelerator1 + 0.09;
//        accelerator2 = accelerator2 + 0.09;
        double velocity = GRAVITY * gravityTimer + 2;
        newY = getHitbox()->y + GRAVITY * pow(gravityTimer, 2) + velocity;
        updateHitboxPos(tmp_x, newY);
        if(newY > 351){
            velocity = 0;
            updateHitboxPos(tmp_x, 351);
        }
    }
}

void Player::Jump() {

    SetJumpTime();

    if (jumpTimer - lastJump > 180) {
//        accelerator1 = 0;
//        accelerator2 = 0;
        jumping = true;
        lastJump = jumpTimer;
    } else {
        Gravity();
    }
}
