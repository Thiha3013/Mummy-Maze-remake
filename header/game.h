#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include <string>

class Game {
public:
    Game();
    ~Game();

    void init();
    void run();
    void cleanup();

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* texture;
    SDL_Event e;
    bool running;

    SDL_Rect dot;
    SDL_Rect mummy;
    SDL_Rect exit;

    std::vector<SDL_Rect> walls;
    std::vector<SDL_Rect> bounds;

    SDL_Texture* dotTexture;

    void readInitialPositions(const std::string& filename);
    void drawCompleteWall(const std::string& filename);
    void drawWall(std::string i, int row, int col);
    void move(char dir);
    void mummymove();
    bool checkCollision(const SDL_Rect& a, const SDL_Rect& b);
    bool checkCollisionWithAny(const SDL_Rect& obj1, const std::vector<SDL_Rect>& objs);
    SDL_Texture* loadTexture(const std::string& filename);
};

#endif