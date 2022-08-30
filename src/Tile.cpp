#include "Math.h"
#include "../include/Tile.hpp"
#include <SDL_render.h>

Tile::Tile(float p_x, float p_y, SDL_Texture* p_tex)
        :Entity(p_x, p_y ,p_tex) {
}