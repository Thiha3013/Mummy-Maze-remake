#include "game.h"
#include "utils.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <cctype>

Game::Game() : window(nullptr), renderer(nullptr), texture(nullptr), dotTexture(nullptr), mummyTexture(nullptr), currentFrame(0), running(true) {
    dot = {-100, -100, 90, 90};
    mummy = {-200, -200, 90, 90};
    exit = {-300, -300, 100, 100};
    bg = {100, 100, 600, 600};
}

Game::~Game() {
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Game::init() {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        std::cout << "Initialization failed: " << SDL_GetError() << std::endl;
        return;
    }

    window = SDL_CreateWindow("Mummy Maze", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 800, 0);
    renderer = SDL_CreateRenderer(window, -1, 0);

    loadTexturesfromIMG();
    readInitialPositions("./data/maps/map6_c.csv");
    drawCompleteWorld("./data/maps/map6_w.csv");
}

void Game::run() {
    char explorerDir = 0;
    char mummyDir = 0;

    if (explorerDir == 0 || mummyDir == 0){
                renderGameElements('d','d',0);
    }
    while (running) {
        
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                running = false;
            } else if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    case SDLK_RIGHT:
                        explorerDir = 'r';
                        break;
                    case SDLK_LEFT:
                        explorerDir = 'l';
                        break;
                    case SDLK_UP:
                        explorerDir = 'u';
                        break;
                    case SDLK_DOWN:
                        explorerDir = 'd';
                        break;
                }
                if (mummy.x < dot.x) mummyDir = 'r';
                else if (mummy.x > dot.x) mummyDir = 'l';
                else if (mummy.y < dot.y) mummyDir = 'd';
                else if (mummy.y > dot.y) mummyDir = 'u';

                

                move(explorerDir);
                mummymove();

                if (checkCollision(dot, exit)) {
                    std::cout << "Congratulations! You won the game!" << std::endl;
                    running = false;
                }
                if (checkCollision(dot, mummy)) {
                    std::cout << "You Died!" << std::endl;
                    running = false;
                }
            }
        }
    }
}


void Game::cleanup() {
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}



void Game::loadTexturesfromIMG() {
    explorerTextures[0] = loadTexture("./data/assets/player/move_up.png");
    explorerTextures[1] = loadTexture("./data/assets/player/move_down.png");
    explorerTextures[2] = loadTexture("./data/assets/player/move_right.png");
    explorerTextures[3] = loadTexture("./data/assets/player/move_left.png");

    mummyTextures[0] = loadTexture("data/assets/enemy/whiteup.png");
    mummyTextures[1] = loadTexture("data/assets/enemy/whitedown.png");
    mummyTextures[2] = loadTexture("data/assets/enemy/whiteright.png");
    mummyTextures[3] = loadTexture("data/assets/enemy/whiteleft.png");

    wallTexture = loadTexture("data/assets/world/walls_sm.gif");
    exitTexture = loadTexture("data/assets/world/stairs.gif");
    bgTexture = loadTexture("data/assets/world/floor.jpg");
}

SDL_Texture* Game::loadTexture(const std::string& filename){
    SDL_Surface* surface = IMG_Load(filename.c_str());
    if (surface == nullptr){
        return nullptr;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    return texture;
}

void Game::renderGameElements(char explorerDir, char mummyDir, int frame) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    loadWorld();
    loadExit();
    loadExplorer(explorerDir);
    loadMummy(mummyDir);

    if (explorerDir != 0) {
        SDL_RenderCopy(renderer, dotTexture, &dotSrc[frame], &dot);
    } else {
        SDL_RenderCopy(renderer, dotTexture, &dotSrc[0], &dot);
    }

    if (mummyDir != 0) {
        SDL_RenderCopy(renderer, mummyTexture, &mummySrc[frame], &mummy);
    } else {
        SDL_RenderCopy(renderer, mummyTexture, &mummySrc[0], &mummy);
    }

    SDL_RenderPresent(renderer);
    SDL_Delay(50);
}

void Game::loadExplorer(char dir){
    switch(dir){
        case 'u':
            dotTexture = explorerTextures[0];
            break;
        case 'd':
            dotTexture = explorerTextures[1];
            break;
        case 'r':
            dotTexture = explorerTextures[2];
            break;
        case 'l':
            dotTexture = explorerTextures[3];
            break;
    }

    if (dotTexture == nullptr) {
        return;
    }

    int textureX, textureY;
    SDL_QueryTexture(dotTexture, NULL, NULL, &textureX, &textureY);

    dotSrc[0].x = 0;
    dotSrc[0].y = 0;
    dotSrc[0].w = textureX/5;
    dotSrc[0].h = textureY;

    dotSrc[1].x = (textureX/5);
    dotSrc[1].y = 0;
    dotSrc[1].w = textureX/5;
    dotSrc[1].h = textureY;

    dotSrc[2].x = 2 * (textureX/5);
    dotSrc[2].y = 0;
    dotSrc[2].w = textureX/5;
    dotSrc[2].h = textureY;

    dotSrc[3].x = 3 * (textureX/5);
    dotSrc[3].y = 0;
    dotSrc[3].w = textureX/5;
    dotSrc[3].h = textureY;

    dotSrc[4].x = 4 * (textureX/5);
    dotSrc[4].y = 0;
    dotSrc[4].w = textureX/5;
    dotSrc[4].h = textureY;
}

void Game::loadMummy(char dir){
    switch(dir){
        case 'u':
            mummyTexture = mummyTextures[0];
            break;
        case 'd':
            mummyTexture = mummyTextures[1];
            break;
        case 'r':
            mummyTexture = mummyTextures[2];
            break;
        case 'l':
            mummyTexture = mummyTextures[3];
            break;
    }

    if (mummyTexture == nullptr) {
        return;
    }

    int textureX, textureY;
    SDL_QueryTexture(mummyTexture, NULL, NULL, &textureX, &textureY);

    mummySrc[0].x = 0;
    mummySrc[0].y = 0;
    mummySrc[0].w = textureX/5;
    mummySrc[0].h = textureY;

    mummySrc[1].x = (textureX/5);
    mummySrc[1].y = 0;
    mummySrc[1].w = textureX/5;
    mummySrc[1].h = textureY;

    mummySrc[2].x = 2 * (textureX/5);
    mummySrc[2].y = 0;
    mummySrc[2].w = textureX/5;
    mummySrc[2].h = textureY;

    mummySrc[3].x = 3 * (textureX/5);
    mummySrc[3].y = 0;
    mummySrc[3].w = textureX/5;
    mummySrc[3].h = textureY;

    mummySrc[4].x = 4 * (textureX/5);
    mummySrc[4].y = 0;
    mummySrc[4].w = textureX/5;
    mummySrc[4].h = textureY;
}

void Game::loadWorld(){
    SDL_RenderCopy(renderer, bgTexture, nullptr, &bg);

    for (const auto& wall : walls) {
        if (wall.w > wall.h) { // Horizontal wall
            wallSrc = {12, 0, 65, 10};
            SDL_RenderCopy(renderer, wallTexture, &wallSrc, &wall);
        } else { // Vertical wall
            wallSrc = {0, 0, 5, 77};
            SDL_RenderCopy(renderer, wallTexture, &wallSrc, &wall);
        }
    }
}

void Game::loadExit(){
    int textureX, textureY;
    SDL_QueryTexture(exitTexture, NULL, NULL, &textureX, &textureY);
    exitSrc.w = textureX/4;
    exitSrc.h = textureY;
    if (exit.y <= 100) { //at the top
        exitSrc.y = 0;
        exitSrc.x = 0;
    }
    else if (exit.y >= 700) { //at the bottom
        exitSrc.y = 0;
        exitSrc.x = 2 * (textureX/4);
    }
    else if (exit.x <= 100) { //at the left
        exitSrc.y = 0;
        exitSrc.x = (textureX/4);
    }
    else if (exit.x >= 700) { // at the right
        exitSrc.y = 0;
        exitSrc.x = 3 * (textureX/4);
    }

    SDL_RenderCopy(renderer, exitTexture, &exitSrc, &exit);
}



void Game::drawWorld(std::string i, int row, int col) {
    int textureX, textureY;

    SDL_Rect wall;
    if (i == "0") {
        // Do nothing
    }
    else if (i == "E"){
        exit = {(col * 100), (row * 100), 100, 100};
    }
    else if (i == "B") {
        wall = {(col * 100), (row * 100), 100, 100};
        walls.push_back(wall);
    }
    else if (i == "1") {
        wall = {(col * 100) - 5, (row * 100) - 5, 100, 10};
        walls.push_back(wall);
    }
    else if (i == "2") {
        wall = {(col * 100) - 5, (row * 100) - 5, 10, 100};
        walls.push_back(wall);
    }
    else if (i == "3") {
        wall = {(col * 100) - 5, (row * 100) - 5, 10, 100};
        walls.push_back(wall);
        wall = {(col * 100) - 5, (row * 100) - 5, 100, 10};
        walls.push_back(wall);
    }
}



void Game::readInitialPositions(const std::string& filename) {
    std::ifstream file(filename);
    std::string line;
    int row = 0, col = 0;

    while (std::getline(file, line)) {
        line = removeBOM(line);
        std::stringstream ss(line);
        std::string cell;
        col = 0;

        while (std::getline(ss, cell, ',')) {
            cell = trim(cell);
            
            if (cell == "M") mummy = {(col * 100)+5, (row * 100)+5, 90, 90};
            else if (cell == "C") dot = {(col * 100)+5, (row * 100)+5, 90, 90};
            else if (cell == "T"){    
                // Add trap position to a vector or data structure
                //traps.emplace_back(SDL_Rect{col * 100, row * 100, 90, 90});
            }   
            col++;
        }
        row++;      
    }
}

void Game::drawCompleteWorld(const std::string& filename) {
    std::ifstream file(filename);
    std::string line;
    int row = 0, col = 0;

    while (std::getline(file, line)) {
        line = removeBOM(line);
        std::stringstream ss(line);
        std::string cell;
        col = 0;

        while (std::getline(ss, cell, ',')) {
            cell = trim(cell);
            drawWorld(cell, row, col);
            col++;
        }
        row++;
    }
}

void Game::move(char dir) {
    char mummyDir = 0;
    currentFrame = 0; // Reset currentFrame to 0

    for (int i = 0; i < 5; i++) {
        int prevx = dot.x;
        int prevy = dot.y;

        switch (dir) {
            case 'r':
                dot.x += 20;
                break;
            case 'l':
                dot.x -= 20;
                break;
            case 'u':
                dot.y -= 20;
                break;
            case 'd':
                dot.y += 20;
                break;
        }

        if (checkCollisionWithAny(dot, walls)) {
            dot.x = prevx;
            dot.y = prevy;
            return;
        }

        // Update mummyDir based on the new positions of the explorer and the mummy
        if (mummy.x < dot.x) mummyDir = 'r';
        else if (mummy.x > dot.x) mummyDir = 'l';
        else if (mummy.y < dot.y) mummyDir = 'd';
        else if (mummy.y > dot.y) mummyDir = 'u';

        // Render the game elements after each move
        renderGameElements(dir, mummyDir, currentFrame);
        currentExplorerFrame = currentFrame; // Update currentExplorerFrame
        currentFrame = (currentFrame + 1) % 4; // Update currentFrame
    }
    currentFrame = 0;
}

void Game::mummymove() {
    char mummyDir = 0;
    currentMummyFrame = 0; // Reset currentMummyFrame to 0

    for (int i = 0; i < 2; i++) { // Outer loop for two grid moves
        int mummyprevx = mummy.x, mummyprevy = mummy.y;
        bool movedHorizontally = false;
        bool movedVertically = false; 

        int horiDist = dot.x - mummy.x;
        int vertDist = dot.y - mummy.y;

        if (horiDist != 0) {
            for (int j = 0; j < 5; j++) { // Inner loop for 5 frames per grid move
                mummy.x += (horiDist > 0) ? 20 : -20;
                if (!checkCollisionWithAny(mummy, walls)) {
                    movedHorizontally = true;
                    if (horiDist > 0) mummyDir = 'r';
                    else mummyDir = 'l';
                } else {
                    mummy.x = mummyprevx;
                    break;
                }

                // Render the mummy after each move
                renderGameElements(0, mummyDir, currentMummyFrame);
                currentMummyFrame = (currentMummyFrame + 1) % 4; // Update currentMummyFrame
            }
            currentMummyFrame = 0;
        }

        if (!movedHorizontally && vertDist != 0) {
            for (int j = 0; j < 5; j++) { // Inner loop for 5 frames per grid move
                mummy.y += (vertDist > 0) ? 20 : -20;
                if (!checkCollisionWithAny(mummy, walls)) {
                    movedVertically = true;
                    if (vertDist > 0) mummyDir = 'd';
                    else mummyDir = 'u';
                } else {
                    mummy.y = mummyprevy;
                    break;
                }

                // Render the mummy after each move
                renderGameElements(0, mummyDir, currentMummyFrame);
                currentMummyFrame = (currentMummyFrame + 1) % 4; // Update currentMummyFrame
            }
            currentMummyFrame = 0;
        }
    }
}


bool Game::checkCollision(const SDL_Rect& a, const SDL_Rect& b) {
   int leftA, leftB;
   int rightA, rightB;
   int topA, topB;
   int bottomA, bottomB;

   leftA = a.x;
   rightA = a.x + a.w;
   topA = a.y;
   bottomA = a.y + a.h;

   leftB = b.x;
   rightB = b.x + b.w;
   topB = b.y;
   bottomB = b.y + b.h;

   if (bottomA <= topB) {
       return false;
   }
   if (topA >= bottomB) {
       return false;
   }
   if (rightA <= leftB) {
       return false;
   }
   if (leftA >= rightB) {
       return false;
   }

   return true;
}

bool Game::checkCollisionWithAny(const SDL_Rect& obj1 , const std::vector<SDL_Rect>& objs) {
   for (const auto& wall : objs) {
       if (checkCollision(obj1, wall)) return true;
   }
   return false;
}