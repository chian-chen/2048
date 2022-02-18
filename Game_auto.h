#ifndef Auto_GAME_IS_FUN
#define Auto_GAME_IS_FUN

#include <stdio.h>
#include "Board_autoplay.h"
#include "Direction_auto.h"

class Game
{

private:
    int score;
    Board *board;

public:
    Game();
    ~Game();
    Direction read_input();
    void printScore();
    void start();
    int getScore();
    void autoPlay();
};

#endif