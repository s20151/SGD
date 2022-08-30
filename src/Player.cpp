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

void Player::Gravity() {
//    double tmp_fdt = (getDt() - getPdt())/1000;
//    if (getJumping()){
//        double tmp_dest = getDest().y;
//        double velocity = gravity * tmp_fdt + 20;
//        double y = getDest().y - 22 * tmp_fdt + 4.5 * tmp_fdt * tmp_fdt * gravity;
//        setDest(40, y, 42, 60);
//        if (tmp_dest < y) {
//            setFdt();
//            setPdt();
//            jumping = false;
//        }
//    }
//    else
//    {
//        double velocity = gravity * tmp_fdt;
//        int y = getDest().y + gravity * tmp_fdt * tmp_fdt + velocity;
//        setDest(40, y, 42, 60);
//    }
}

void Player::update(float deltaTime, bool moveLeft, bool moveRight, bool jump,
                    std::vector<Entity> floor,std::vector<Entity> spikes) {
    updateCurrentFrame(getX(), getY());

    if(moveRight){
        setX(getX() + 1);
    }

    if(moveLeft){

    }

    if(jump){

    }

    for (Entity f: floor) {
        if(SDL_HasIntersection(getCurrentFrame(), f.getCurrentFrame())){

        }
    }
    for (Entity s: spikes) {
        if (SDL_HasIntersection(getCurrentFrame(), s.getCurrentFrame())){
            setX(0);
            setY(351);
            jump = false;
            moveLeft = false;
            moveRight = false;
        }
    }
}