#include "../include/Entity.hpp"
#include <SDL.h>

Entity::Entity(double p_x, double p_y, SDL_Texture* texture)
        : tex(texture) {
    hitbox.x = p_x;
    hitbox.y = p_y;
    hitbox.w = 25;
    hitbox.h = 25;
}

SDL_Texture* Entity::getTex() {
    return tex;
}

void Entity::updateHitboxPos(double p_x, double p_y) {
    hitbox.x = p_x;
    hitbox.y = p_y;
}

const SDL_Rect * Entity::getHitbox() {
    return &hitbox;
};
