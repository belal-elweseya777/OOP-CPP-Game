#include "Board.h"

Board::Board() {
    clear();
}

void Board::clear() {
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
            grid[i][j] = 0; // puts 0 in all cells or empty
}

bool Board::checkWin(int p) {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (grid[i][j] == p) {
                if (j <= 5 && grid[i][j + 1] == p && grid[i][j + 2] == p && grid[i][j + 3] == p && grid[i][j + 4] == p) return true;
                if (i <= 5 && grid[i + 1][j] == p && grid[i + 2][j] == p && grid[i + 3][j] == p && grid[i + 4][j] == p) return true;
                if (i <= 5 && j <= 5 && grid[i + 1][j + 1] == p && grid[i + 2][j + 2] == p && grid[i + 3][j + 3] == p && grid[i + 4][j + 4] == p) return true;
                if (i <= 5 && j >= 4 && grid[i + 1][j - 1] == p && grid[i + 2][j - 2] == p && grid[i + 3][j - 3] == p && grid[i + 4][j - 4] == p) return true;
            }
        }
    }
    return false;
}