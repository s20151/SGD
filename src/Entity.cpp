#include "../include/Entity.hpp"
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>

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


void Entity::update(double deltaTime, bool moveLeft, bool moveRight, bool jump,
                    std::vector<Entity> floor,std::vector<Entity> spikes) {

    for (Entity f: floor) {

    }
    for (Entity s: spikes) {
        if (getX() + 25 == s.getX() || getY() + 25 > s.getY()) {
            setX(0);
            setY(351);
            jump = false;
            moveLeft = false;
            moveRight = false;
        }
    }
}