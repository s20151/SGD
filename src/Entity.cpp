#include "../include/Entity.hpp"
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>

const int GRAVITY = 0.1;

Entity::Entity(double p_x, double p_y, SDL_Texture* texture)
        : tex(texture) {
    currentFrame.x = p_x;
    currentFrame.y = p_y;
    currentFrame.w = 25;
    currentFrame.h = 25;
}

SDL_Texture* Entity::getTex() {
    return tex;
}

void Entity::updateCurrentFrame(double p_x, double p_y) {
    currentFrame.x = p_x;
    currentFrame.y = p_y;
}

const SDL_Rect * Entity::getCurrentFrame(){
    return &currentFrame;
};
