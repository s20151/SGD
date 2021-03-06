#include "../include/Entity.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

const int GRAVITY = 1;

Entity::Entity(float p_x, float p_y, SDL_Texture* texture)
        :x(p_x), y(p_y), tex(texture), jumping(false),
        falling(true), jumpspeed(-20), yVel(0){
    currentFrame.x = x;
    currentFrame.y = y;
    currentFrame.w = 50;
    currentFrame.h = 50;
}

float Entity::getX() {
    return x;
}

float Entity::getY() {
    return y;
}

SDL_Texture* Entity::getTex() {
    return tex;
}

void Entity::setX(float p_x){
    x=p_x;
}
void Entity::setY(float p_y){
    y=p_y;
}
void Entity::updateCurrentFrame(float p_x, float p_y) {
    currentFrame.x = p_x;
    currentFrame.y = p_y;
}
const SDL_Rect * Entity::getCurrentFrame(){
    return &currentFrame;
};

void Entity::jump() {
    if(jumping) {
        falling = false;
        jumpspeed += GRAVITY;
        if(jumpspeed > 0) {
            jumping = false;
            falling = true;
        }
        yVel = jumpspeed;
    }

    if(falling && jumpspeed < 21) {
        jumpspeed += GRAVITY;
        yVel = jumpspeed;
    }

    if(jumpspeed >= 20) {
        falling = false;
        jumpspeed = -20;
    }
    setY(getY() + yVel);
}

void Entity:: setFalling(bool p_f) {
    falling = p_f;
}

void Entity:: setJumping(bool p_j) {
    jumping = p_j;
}
void Entity::setJumpspeed(int speed) {
    jumpspeed = speed;
}

void Entity::update(int x){
    switch (x) {
        case 1:
            setX(getX()+3);
            break;
        case 2:
            setX(getY()-3);
            break;
        case 3:
            do {
                jump();
                std::cout<<getY()<<std::endl;
            }while(getY()!=351);
            break;
    }
}
