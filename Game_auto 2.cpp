#include "Game_auto.h"
#include "Direction_auto.h"
#include <iostream>

using namespace std;

Game::Game()
{
    score = 0;
    board = new Board();
}
Game::~Game()
{
    delete board;
}

Direction Game::read_input()
{
    char direction;
    cin >> direction;
    if (direction == 'e')
        return UP;
    else if (direction == 'd')
        return DOWN;
    else if (direction == 's')
        return LEFT;
    else if (direction == 'f')
        return RIGHT;
    else
        return INVALID;
}
void Game::printScore()
{
    cout << "score: " << score << endl;
}

void Game::start()
{
    bool EndGame = board->checkGameOver();
    while (!EndGame)
    {
        printScore();
        board->displayBoard();
        Direction direction = read_input();
        score += board->moveBoard(direction);
        EndGame = board->checkGameOver();
    }
    printScore();
    board->displayBoard();
    cout << "Game Over!" << endl;
}

// ******     up right down left
// void Game::autoPlay()
// {
//     bool EndGame = board->checkGameOver();
//     while (!EndGame)
//     {
//         score += board->moveBoard(UP);
//         score += board->moveBoard(RIGHT);
//         score += board->moveBoard(DOWN);
//         score += board->moveBoard(LEFT);
//         EndGame = board->checkGameOver();
//     }
// }

// void Game::autoPlay()
// {
//     bool EndGame = board->checkGameOver();
//     while (!EndGame)
//     {
//         score += board->GreedySolution();
//         EndGame = board->checkGameOver();
//     }
//     return;
// }

void Game::autoPlay()
{
    bool EndGame = board->checkGameOver();
    while (!EndGame)
    {
        score += board->MonteCarloSolution();
        EndGame = board->checkGameOver();
    }
    cout << "Done!\n"
         << "Score: " << score << endl;
    return;
}

int Game::getScore()
{
    return score;
}