#include <SDL.h>

class RenderWindow {

public:
    RenderWindow(const char* title, int width, int height);
    SDL_Texture* loadTexture(const char* filePath);
    void cleanUp();
    void render(SDL_Texture* texture);
    void display();
    void clear();

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
};