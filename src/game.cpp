#include "game.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <cctype>

Game::Game() : window(nullptr), renderer(nullptr), running(true) {
    dot = {-100, -100, 90, 90};
    mummy = {-200, -200, 90, 90};
    exit = {-300, -300, 100, 100};
}

Game::~Game() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Game::init() {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        std::cout << "Initialization failed: " << SDL_GetError() << std::endl;
        return;
    }

    //window = SDL_CreateWindow("Mummy Maze", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 600, 0);
    window = SDL_CreateWindow("Mummy Maze", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 800, 0);
    renderer = SDL_CreateRenderer(window, -1, 0);

    readInitialPositions("./data/map6_c.csv");
    drawCompleteWall("./data/map6_w.csv");
}

void Game::run() {
    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                running = false;
            } else if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    case SDLK_RIGHT:
                        move('r');
                        break;
                    case SDLK_LEFT:
                        move('l');
                        break;
                    case SDLK_UP:
                        move('u');
                        break;
                    case SDLK_DOWN:
                        move('d');
                        break;
                }
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

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        for (const auto& wall : walls) {
            SDL_RenderFillRect(renderer, &wall);
        }
        for (const auto& bound : bounds) {
            SDL_RenderFillRect(renderer, &bound);
        }
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
        SDL_RenderFillRect(renderer, &dot);
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderFillRect(renderer, &mummy);

        SDL_RenderPresent(renderer);
        SDL_Delay(25);
    }
}

void Game::cleanup() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Game::drawWall(std::string i, int row, int col) {
    SDL_Rect wall;
    if (i == "0") {
        // Do nothing
    }
    else if (i == "E"){
        //exit = {(col * 100) - 100, (row * 100) - 100, 100, 100};
        exit = {(col * 100), (row * 100), 100, 100};
    }
    else if (i == "B") {
        //wall = {(col * 100) - 100, (row * 100) - 100, 100, 100};
        wall = {(col * 100), (row * 100), 100, 100};
        walls.push_back(wall);
    }
    else if (i == "1") {
        //wall = {(col * 100) - 105, (row * 100) - 105, 100, 10};
        wall = {(col * 100) - 5, (row * 100) - 5, 100, 10};
        walls.push_back(wall);
    }
    else if (i == "2") {
        //wall = {(col * 100) - 105, (row * 100) - 105, 10, 100};
        wall = {(col * 100) - 5, (row * 100) - 5, 10, 100};
        walls.push_back(wall);
    }
    else if (i == "3") {
        wall = {(col * 100) - 5, (row * 100) - 5, 10, 100};
        walls.push_back(wall);
        wall = {(col * 100) - 5, (row * 100) - 5, 100, 10}; // Corrected dimensions
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

void Game::drawCompleteWall(const std::string& filename) {
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
            drawWall(cell, row, col);
            col++;
        }
        row++;
        //std::cout << std::endl;
    }
}

void Game::move(char dir) {
    for (int i = 0; i < 2; i++) {
        int prevx = dot.x;
        int prevy = dot.y;

        switch (dir) {
            case 'r':
                dot.x += 50;
                break;
            case 'l':
                dot.x -= 50;
                break;
            case 'u':
                dot.y -= 50;
                break;
            case 'd':
                dot.y += 50;
                break;
        }

        if (checkCollisionWithAny(dot, walls)) {
            dot.x = prevx;
            dot.y = prevy;
            return;
        }
    }
}

void Game::mummymove() {
    for (int i = 0; i < 2; i++) {
        int mummyprevx = mummy.x, mummyprevy = mummy.y;
        bool movedHorizontally = false;
        bool movedVertically = false;

        int horiDist = dot.x - mummy.x;
        int vertDist = dot.y - mummy.y;

        if (horiDist != 0) {
            for (int j = 0; j < 2; j++) {
                mummy.x += (horiDist > 0) ? 50 : -50;
                if (!checkCollisionWithAny(mummy, walls)) {
                    movedHorizontally = true;
                } else {
                    mummy.x = mummyprevx;
                    break;
                }
            }
        }

        if (movedHorizontally)
            continue;

        if (vertDist != 0) {
            for (int j = 0; j < 2; j++) {
                mummy.y += (vertDist > 0) ? 50 : -50;
                if (!checkCollisionWithAny(mummy, walls)) {
                    movedVertically = true;
                } else {
                    mummy.y = mummyprevy;
                    break;
                }
            }
        }

        if (movedVertically)
            continue;
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

std::string Game::trim(const std::string& str) {
    std::string result = str;
    result.erase(result.begin(), std::find_if(result.begin(), result.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
    result.erase(std::find_if(result.rbegin(), result.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), result.end());
    return result;
}

std::string Game::removeBOM(const std::string& str) {
    if (str.size() >= 3 && str[0] == '\xEF' && str[1] == '\xBB' && str[2] == '\xBF') {
        return str.substr(3);
    }
    return str;
}