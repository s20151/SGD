#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "Entity.hpp"
#include "Math.h"

class Tile : public Entity {
public:
    Tile(float p_x, float p_y, SDL_Texture* p_tex);

private:
};