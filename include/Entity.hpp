#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Entity {
public:
    Entity(float p_x, float p_y, SDL_Texture* texture);
    float getX();
    float getY();
    void setX(float p_x);
    void setY(float p_y);
    SDL_Texture* getTex();
    const SDL_Rect * getCurrentFrame();
    void updateCurrentFrame(float p_x, float p_y);
    void jump();
    void setJumping(bool p_j);
    void setFalling(bool p_f);
    void setJumpspeed(int speed);
    void update(int x);
private:
    float x, y;
    bool jumping, falling;
    int jumpspeed;
    int yVel;
    SDL_Rect currentFrame;
    SDL_Texture* tex;
};
