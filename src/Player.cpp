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
        : Entity{ p_x, p_y, texture}, xVel(0), yVel(0) {
}

void Player::Gravity(float deltaTime) {

}

void Player:: Jump(){

}

void Player::update(float deltaTime, bool moveLeft, bool moveRight, bool jump,
                    std::vector<Entity> floor,std::vector<Entity> spikes) {

    if(moveRight){
        updateCurrentFrame((getCurrentFrame()->x + xVel * (double)deltaTime), getCurrentFrame()->x);
    }

    if(moveLeft){
        updateCurrentFrame((getCurrentFrame()->y + yVel * (double)deltaTime), getCurrentFrame()->y);
    }

    if(jump && !jumping){
        jumping = true;

    }
    // disable gravity/jump
    for (Entity f: floor) {
        if(SDL_HasIntersection(getCurrentFrame(), f.getCurrentFrame())){
            jumping = false;
        }
    }
    // kill and return to spawn
    for (Entity s: spikes) {
        if (SDL_HasIntersection(getCurrentFrame(), s.getCurrentFrame())){

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

bool Player::getAccelerating() {
    return accelerating;
}

