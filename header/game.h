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
    SDL_Rect bg;

    int currentFrame;
    int currentMummyFrame;
    int currentExplorerFrame;

    SDL_Rect dotSrc[5];
    SDL_Rect mummySrc[5];
    

    std::vector<SDL_Rect> walls;
    SDL_Rect exit;

    SDL_Rect wallSrc;
    SDL_Rect exitSrc;

    
    SDL_Texture* dotTexture;
    SDL_Texture* mummyTexture;
    SDL_Texture* bgTexture;

    SDL_Texture* wallTexture;
    SDL_Texture* exitTexture;

    SDL_Texture* explorerTextures[4];
    SDL_Texture* mummyTextures[4];

    void readInitialPositions(const std::string& filename);
    void drawCompleteWorld(const std::string& filename);
    void drawWorld(std::string i, int row, int col);
    void move(char dir);
    void mummymove();
    bool checkCollision(const SDL_Rect& a, const SDL_Rect& b);
    bool checkCollisionWithAny(const SDL_Rect& obj1, const std::vector<SDL_Rect>& objs);
    SDL_Texture* loadTexture(const std::string& filename);
    void loadExplorer(char Dir);
    void loadMummy(char Dir);
    void loadWorld();
    void loadExit();
    void renderGameElements(char explorerDir, char mummyDir, int currentFrame);
    void loadTexturesfromIMG();
};

#endif