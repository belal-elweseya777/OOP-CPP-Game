#ifndef BOARD_H
#define BOARD_H

class Board {
public:
    int grid[10][10];

    Board();
    void clear();
    bool checkWin(int p);
};

#endif