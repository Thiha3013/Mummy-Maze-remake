#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
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
    SDL_Event e;
    SDL_Rect dot;
    SDL_Rect mummy;
    SDL_Rect exit = {-100, -100, 100, 100};
    std::vector<SDL_Rect> walls;
    std::vector<SDL_Rect> bounds;
    std::vector<SDL_Rect> traps; // Add this line
    bool running;

    void drawWall(std::string i, int row, int col);
    void drawCompleteWall(const std::string& filename);
    void readInitialPositions(const std:: string& filename);
    void move(char dir);
    void mummymove();
    bool checkCollision(const SDL_Rect& a, const SDL_Rect& b);
    bool checkCollisionWithAny(const SDL_Rect& obj1, const std::vector<SDL_Rect>& objs);
    std::string trim(const std::string& str);
    std::string removeBOM(const std::string& str);
};

#endif // GAME_H