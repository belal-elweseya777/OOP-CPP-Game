#include "AI.h"
#include <cstdlib>
#include <vector>

int evaluateLine(int count, int openEnds) {
    if (count >= 4) return 10000;
    if (count == 3) return (openEnds == 2) ? 5000 : 500;
    if (count == 2) return (openEnds == 2) ? 100 : 10;
    return 0;
}

void AI::play(Board& b, int ai, int user, int difficulty) {
    // Generate a random chance between 1 and 100
    int chance = rand() % 100 + 1;
    bool makeRandomMove = false;

    if (difficulty == 1 && chance <= 80) makeRandomMove = true;      // 80% random for Very Easy
    else if (difficulty == 2 && chance <= 10) makeRandomMove = true; // Only 10% random for Medium

    if (makeRandomMove) {
        std::vector<std::pair<int, int>> emptyCells;
        for (int r = 0; r < 10; r++) {
            for (int c = 0; c < 10; c++) {
                if (b.grid[r][c] == 0) emptyCells.push_back({ r, c });
            }
        }
        if (!emptyCells.empty()) {
            int randomIndex = rand() % emptyCells.size();
            b.grid[emptyCells[randomIndex].first][emptyCells[randomIndex].second] = ai;
            return;
        }
    }

    int bestScore = -1; // Stores the highest score found
    int bestR = -1, bestC = -1; // Stores coordinates for the best move

    // Directions to check: Horizontal, Vertical, Diagonal (Right & Left)
    int dirs[4][2] = { {0,1}, {1,0}, {1,1}, {1,-1} };

    // Full board scan to evaluate every empty cell
    for (int r = 0; r < 10; r++) {
        for (int c = 0; c < 10; c++) {
            if (b.grid[r][c] == 0) {
                int score = 0;

                // Evaluate threats and opportunities in all 4 directions
                for (int d = 0; d < 4; d++) {
                    int players[2] = { user, ai };

                    for (int PIndex = 0; PIndex < 2; PIndex++) {
                        int p = players[PIndex];
                        int count = 0, openEnds = 0;
                        int directions[2] = { 1, -1 };
                        for (int s = 0; s < 2; s++) {
                            int side = directions[s];
                            for (int step = 1; step < 5; step++) {
                                int nr = r + dirs[d][0] * step * side;
                                int nc = c + dirs[d][1] * step * side;

                                // Boundary check for 10x10 matrix
                                if (nr >= 0 && nr < 10 && nc >= 0 && nc < 10) {
                                    if (b.grid[nr][nc] == p) count++;
                                    else {
                                        if (b.grid[nr][nc] == 0) openEnds++; // Detect open ends for the chain
                                        break;
                                    }
                                }
                                else break;
                            }
                        }

                        // Get the weight of the current sequence
                        int val = evaluateLine(count, openEnds);

                        if (p == ai && count >= 4) score += 20000; // Maximum priority for winning move
                        else score += (p == user) ? (int)(val * 1.5) : val; // Priority multiplier for defense (1.5x)
                    }
                }

                // Update the best move if the  cell has a higher score
                if (score > bestScore) {
                    bestScore = score;
                    bestR = r;
                    bestC = c;
                }
            }
        }
    }

    // Execute the move in the best location
    if (bestR != -1) {
        b.grid[bestR][bestC] = ai;
    }
}