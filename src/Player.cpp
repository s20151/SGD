#include <SDL.h>
#include <SDL_events.h>
#include <SDL_image.h>
#include <cmath>
#include <vector>
#include <string>

#include "../include/Player.hpp"
#include "../include/Entity.hpp"

const float GRAVITY = 0.09f;
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 400;

Player::Player(float p_x, float p_y, SDL_Texture* texture)
        : Entity{ p_x, p_y, texture} {
}

void Player::jump() {
    if(onGround){
        velocityY=-(1/50 * 200);
        onGround = false;
    }
}

void Player::moveRight() {
    velocityX = 1/50*100;
}

void Player::moveLeft() {
    velocityX = 1/50*-100;
}
