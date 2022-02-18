
#include <iostream>
#include "Game_auto.h"

using namespace std;

int main(void)
{
    int acc_score = 0;
    for (int i = 0; i < 10; i++)
    {
        Game *game = new Game();
        game->autoPlay();
        acc_score += game->getScore();
        delete game;
    }
    cout << "Average score: " << (double)acc_score / 10 << endl;
    return 0;
}