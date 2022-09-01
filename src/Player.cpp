#include <SDL.h>
#include <SDL_events.h>
#include <vector>
#include "../include/Player.hpp"

const double GRAVITY = 2.2;
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
            accelerator1 = 0;
            accelerator2 = 0;
            standing = true;
        }
    }
    // after touching floor disable gravity/jump
    for (Entity f: floor) {
        if (SDL_HasIntersection(getHitbox(), f.getHitbox())) {
            standing = true;
            updateHitboxPos(getHitbox()->x, f.getHitbox()->y-25);
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

void Player::SetJumpTime() {
    jumpTimer = SDL_GetTicks();
}

void Player::Gravity() {

    SetJumpTime();

    if (getJumping()) {
        accelerator1 = accelerator1 + 0.03;
        accelerator2 = accelerator2 + 0.1;
        jumpHeight = jumpHeight + GRAVITY;
        updateHitboxPos(tmp_x, getHitbox()->y + GRAVITY + accelerator1 + accelerator2 + jumpHeight);
        if (jumpHeight > 0) {
            jumping = false;
            jumpHeight = -25;
        }
    } else {
        accelerator1 = accelerator1 + 0.09;
        accelerator2 = accelerator2 + 0.09;
        updateHitboxPos(tmp_x, getHitbox()->y + GRAVITY + accelerator1 + accelerator2);
    }
}

void Player::Jump() {
    if (jumpTimer - lastJump > 180) {
        accelerator1 = 0;
        accelerator2 = 0;
        jumping = true;
        lastJump = jumpTimer;
    } else {
        Gravity();
    }
}