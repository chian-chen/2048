#ifndef Auto_BOARD_IS_FUN
#define Auto_BOARD_IS_FUN

#include <stdio.h>
#include "Direction_auto.h"

class Board
{

private:
    char tiles[4][4];

public:
    Board();
    void displayBoard();
    void newTile();
    int moveSingleLine(char line[4], char new_line[4]);
    int moveBoard(Direction dir);
    bool checkGameOver();
    int GreedySolution();
    void CopyTiles(char base[4][4], char copy[4][4]);
    int RandomDirectionToEnd();
    int MonteCarloSolution();
};

#endif