#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <vector>

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
    void update(int x);

    void update(double deltaTime, bool moveLeft, bool moveRight, bool jump, std::vector<Entity> floor,
                std::vector<Entity> spikes);

private:
    float x, y;
    bool jumping, falling;
    int jumpspeed;
    int yVel;
    SDL_Rect currentFrame;
    SDL_Texture* tex;

    void setVelocity(float x, float y);
};
