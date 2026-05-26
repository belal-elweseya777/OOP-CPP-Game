#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>
#include "Board.h"
#include "AI.h"

class Game {
    Board b;
    AI computer;
    int mySide, aiSide;
    bool gameOver, startMenu;
    bool difficultyMenu;
    int difficulty;
    int winner;
    sf::RenderWindow win;

public:
    Game();
    void drawMenu();
    void drawDifficultyMenu();
    void drawGrid();
    void drawShapes();
    void start();
};

#endif