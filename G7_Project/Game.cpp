#include "Game.h"
#include <ctime>

Game::Game() : win(sf::VideoMode(600, 600), "Tic-Tac-Toe G7") {
    srand(time(0));
    startMenu = true;
    difficultyMenu = false;
    gameOver = false;
    winner = 0;
    difficulty = 3;
}

void Game::drawMenu() {
    // Left button for choosing 'X'
    sf::RectangleShape btnX(sf::Vector2f(200, 200));
    btnX.setPosition(50, 200);
    btnX.setFillColor(sf::Color(230, 230, 230));
    btnX.setOutlineThickness(5);
    btnX.setOutlineColor(sf::Color::Blue);
    win.draw(btnX);

    // Draw 'X' shape inside the button
    sf::RectangleShape l(sf::Vector2f(140, 10));
    l.setFillColor(sf::Color::Blue);
    l.setOrigin(70, 5);
    l.setPosition(150, 300);
    l.setRotation(45); win.draw(l);
    l.setRotation(-45); win.draw(l);

    // Right button for choosing 'O'
    sf::RectangleShape btnO(sf::Vector2f(200, 200));
    btnO.setPosition(350, 200);
    btnO.setFillColor(sf::Color(230, 230, 230));
    btnO.setOutlineThickness(5);
    btnO.setOutlineColor(sf::Color::Red);
    win.draw(btnO);

    // Draw 'O' shape inside the button
    sf::CircleShape circ(60);
    circ.setOutlineThickness(10);
    circ.setOutlineColor(sf::Color::Red);
    circ.setFillColor(sf::Color::Transparent);
    circ.setOrigin(60, 60);
    circ.setPosition(450, 300);
    win.draw(circ);
}

void Game::drawDifficultyMenu() {
    // Easy Box
    sf::RectangleShape btnEasy(sf::Vector2f(400, 80));
    btnEasy.setPosition(100, 150);
    btnEasy.setFillColor(sf::Color(0, 255, 0, 120));
    btnEasy.setOutlineThickness(4);
    btnEasy.setOutlineColor(sf::Color::Green);
    win.draw(btnEasy);

    // Medium Box
    sf::RectangleShape btnMed(sf::Vector2f(400, 80));
    btnMed.setPosition(100, 270);
    btnMed.setFillColor(sf::Color(255, 165, 0, 120));
    btnMed.setOutlineThickness(4);
    btnMed.setOutlineColor(sf::Color(255, 165, 0));
    win.draw(btnMed);

    // Hard Box
    sf::RectangleShape btnHard(sf::Vector2f(400, 80));
    btnHard.setPosition(100, 390);
    btnHard.setFillColor(sf::Color(255, 0, 0, 120));
    btnHard.setOutlineThickness(4);
    btnHard.setOutlineColor(sf::Color::Red);
    win.draw(btnHard);
}

void Game::drawGrid() {
    // Draw 10x10 grid lines
    for (int i = 0; i <= 10; i++) {
        // Horizontal lines
        sf::RectangleShape line(sf::Vector2f(600, 1));
        line.setPosition(0, i * 60);
        line.setFillColor(sf::Color(200, 200, 200));
        win.draw(line);

        // Vertical lines
        line.setSize(sf::Vector2f(1, 600));
        line.setPosition(i * 60, 0);
        win.draw(line);
    }
}

void Game::drawShapes() {
    // Iterate through the board matrix to draw X and O
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (b.grid[i][j] == 1) { // Draw 'X' using two rotated rectangles
                sf::RectangleShape s(sf::Vector2f(45, 4));
                s.setFillColor(sf::Color::Blue);
                s.setOrigin(22.5, 2);
                s.setPosition(j * 60 + 30, i * 60 + 30);
                s.setRotation(45); win.draw(s);
                s.setRotation(-45); win.draw(s);
            }
            if (b.grid[i][j] == 2) { // Draw 'O' using a circle shape
                sf::CircleShape c(20);
                c.setOutlineThickness(4);
                c.setOutlineColor(sf::Color::Red);
                c.setFillColor(sf::Color::Transparent);
                c.setPosition(j * 60 + 10, i * 60 + 10);
                win.draw(c);
            }
        }
    }

    if (gameOver) {
        sf::RectangleShape rect(sf::Vector2f(600, 600));
        // Green color if player wins, Red if computer wins
        if (b.checkWin(mySide)) rect.setFillColor(sf::Color(0, 255, 0, 150));
        else rect.setFillColor(sf::Color(255, 0, 0, 150));
        win.draw(rect);
    }
}

void Game::start() {
    while (win.isOpen()) {
        sf::Event e;
        while (win.pollEvent(e)) {
            if (e.type == sf::Event::Closed) win.close();

            if (startMenu && e.type == sf::Event::MouseButtonPressed) {
                int mx = e.mouseButton.x;
                int my = e.mouseButton.y;
                if (mx >= 50 && mx <= 250 && my >= 200 && my <= 400) {
                    mySide = 1; aiSide = 2;
                    startMenu = false; difficultyMenu = true;
                }
                if (mx >= 350 && mx <= 550 && my >= 200 && my <= 400) {
                    mySide = 2; aiSide = 1;
                    startMenu = false; difficultyMenu = true;
                }
            }
            else if (difficultyMenu && e.type == sf::Event::MouseButtonPressed) {
                int mx = e.mouseButton.x;
                int my = e.mouseButton.y;
                if (mx >= 100 && mx <= 500 && my >= 150 && my <= 230) { difficulty = 1; difficultyMenu = false; }
                if (mx >= 100 && mx <= 500 && my >= 270 && my <= 350) { difficulty = 2; difficultyMenu = false; }
                if (mx >= 100 && mx <= 500 && my >= 390 && my <= 470) { difficulty = 3; difficultyMenu = false; }
            }
            else if (!startMenu && !difficultyMenu && e.type == sf::Event::MouseButtonPressed) {
                if (gameOver) { // If game is over, any click resets the board
                    b.clear();
                    gameOver = false;
                    startMenu = true;
                }
                else {
                    int col = e.mouseButton.x / 60;
                    int row = e.mouseButton.y / 60;
                    if (row < 10 && col < 10 && b.grid[row][col] == 0) {
                        b.grid[row][col] = mySide;
                        if (b.checkWin(mySide)) gameOver = true;
                        else {
                            computer.play(b, aiSide, mySide, difficulty);
                            if (b.checkWin(aiSide)) gameOver = true;
                        }
                    }
                }
            }
        }
        win.clear(sf::Color::White);
        if (startMenu) drawMenu();
        else if (difficultyMenu) drawDifficultyMenu();
        else { drawGrid(); drawShapes(); }
        win.display();
    }
}