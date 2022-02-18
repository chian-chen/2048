#include "Board_autoplay.h"
#include "Direction_auto.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

Board::Board()
{
    // srand(time(NULL));
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
            tiles[i][j] = ' ';
    }
    for (int i = 0; i < 2; i++)
    {
        int x = rand() % 4;
        int y = rand() % 4;
        if (tiles[x][y] == ' ')
            tiles[x][y] = 'A';
        else
        {
            i--;
            continue;
        }
    }
}

void Board::displayBoard()
{
    cout << "+---+---+---+---+" << endl;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            cout << "| " << tiles[i][j] << " ";
        }
        cout << "|" << endl;
        cout << "+---+---+---+---+" << endl;
    }
}

void Board::newTile()
{
    // srand(time(NULL));
    while (true)
    {
        int x = rand() % 4;
        int y = rand() % 4;
        int z = rand() % 3;
        if (tiles[x][y] == ' ')
        {
            if (z == 0)
                tiles[x][y] = 'A';
            else if (z == 1)
                tiles[x][y] = 'B';
            else
                tiles[x][y] = 'C';
            return;
        }
        else
            continue;
    }
    return;
}

// A:2 B:4 C:8 D:16 E:32 F:64 G:128 H:256 I:512 J:1024 K:2048
int Board::moveSingleLine(char line[4], char new_line[4])
{
    // make everything left
    int new_index = 0;
    for (int i = 0; i < 4; i++)
        new_line[i] = ' ';
    while (new_index < 4)
    {
        for (int i = new_index; i < 4; i++)
        {
            if (line[i] != ' ')
            {
                new_line[new_index] = line[i];
                line[i] = ' ';
                new_index++;
                continue;
            }
        }
        new_index++;
    }
    // if NULL or only one element
    // return
    if (new_line[0] == ' ' || new_line[1] == ' ')
        return 0;
    // if there are two elements
    if (new_line[2] == ' ')
    {
        if (new_line[0] == new_line[1])
        {
            new_line[0] = char(new_line[0] + 1);
            new_line[1] = ' ';
            return pow(2, (new_line[0] - 'A' + 1));
        }
        return 0;
    }
    // if there are three elements
    if (new_line[3] == ' ')
    {
        if (new_line[0] == new_line[1])
        {
            new_line[0] = char(new_line[0] + 1);
            new_line[1] = new_line[2];
            new_line[2] = ' ';
            return pow(2, (new_line[0] - 'A' + 1));
        }
        else if (new_line[1] == new_line[2])
        {
            new_line[1] = char(new_line[1] + 1);
            new_line[2] = ' ';
            return pow(2, (new_line[1] - 'A' + 1));
        }
        else
            return 0;
    }
    // if there are four elements
    if (new_line[3] != ' ')
    {
        if (new_line[0] == new_line[1] && new_line[2] == new_line[3])
        {
            new_line[0] = char(new_line[0] + 1);
            new_line[1] = char(new_line[2] + 1);
            new_line[2] = ' ';
            new_line[3] = ' ';
            return pow(2, (new_line[0] - 'A' + 1)) + pow(2, (new_line[1] - 'A' + 1));
        }
        else if (new_line[0] == new_line[1])
        {
            new_line[0] = char(new_line[0] + 1);
            new_line[1] = new_line[2];
            new_line[2] = new_line[3];
            new_line[3] = ' ';
            return pow(2, (new_line[0] - 'A' + 1));
        }
        else if (new_line[1] == new_line[2])
        {
            new_line[1] = char(new_line[1] + 1);
            new_line[2] = new_line[3];
            new_line[3] = ' ';
            return pow(2, (new_line[1] - 'A' + 1));
        }
        else if (new_line[2] == new_line[3])
        {
            new_line[2] = char(new_line[2] + 1);
            new_line[3] = ' ';
            return pow(2, (new_line[2] - 'A' + 1));
        }
        else
            return 0;
    }
    return 0;
}

int Board::moveBoard(Direction dir)
{
    int score = 0;
    bool isChange = false;
    if (dir == LEFT)
    {
        for (int i = 0; i < 4; i++)
        {
            char old_one[4];
            char new_one[4];
            for (int j = 0; j < 4; j++)
                old_one[j] = tiles[i][j];
            score += moveSingleLine(old_one, new_one);
            if (!isChange)
                for (int j = 0; j < 4; j++)
                    if (new_one[j] != tiles[i][j])
                    {
                        isChange = true;
                        break;
                    }
            if (isChange)
                for (int j = 0; j < 4; j++)
                    tiles[i][j] = new_one[j];
        }
    }
    else if (dir == RIGHT)
    {
        for (int i = 0; i < 4; i++)
        {
            char old_one[4];
            char new_one[4];
            for (int j = 0; j < 4; j++)
            {
                old_one[j] = tiles[i][3 - j];
            }
            score += moveSingleLine(old_one, new_one);
            if (!isChange)
                for (int j = 0; j < 4; j++)
                    if (new_one[j] != tiles[i][3 - j])
                    {
                        isChange = true;
                        break;
                    }
            if (isChange)
                for (int j = 0; j < 4; j++)
                    tiles[i][3 - j] = new_one[j];
        }
    }
    else if (dir == UP)
    {
        for (int i = 0; i < 4; i++)
        {
            char old_one[4];
            char new_one[4];
            for (int j = 0; j < 4; j++)
            {
                old_one[j] = tiles[j][i];
            }
            score += moveSingleLine(old_one, new_one);
            if (!isChange)
                for (int j = 0; j < 4; j++)
                    if (new_one[j] != tiles[j][i])
                    {
                        isChange = true;
                        break;
                    }
            if (isChange)
                for (int j = 0; j < 4; j++)
                    tiles[j][i] = new_one[j];
        }
    }
    else if (dir == DOWN)
    {
        for (int i = 0; i < 4; i++)
        {
            char old_one[4];
            char new_one[4];
            for (int j = 0; j < 4; j++)
            {
                old_one[j] = tiles[3 - j][i];
            }
            score += moveSingleLine(old_one, new_one);
            if (!isChange)
                for (int j = 0; j < 4; j++)
                    if (new_one[j] != tiles[3 - j][i])
                    {
                        isChange = true;
                        break;
                    }
            if (isChange)
                for (int j = 0; j < 4; j++)
                    tiles[3 - j][i] = new_one[j];
        }
    }
    else
        return 0;
    if (isChange)
        newTile();
    return score;
}

bool Board::checkGameOver()
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
            if (tiles[i][j] == ' ')
                return false;
    }
    for (int i = 0; i < 4; i++)
    {
        char old_one[4];
        char new_one[4];
        for (int j = 0; j < 4; j++)
            old_one[j] = tiles[i][j];
        int score = moveSingleLine(old_one, new_one);
        if (score == 0)
            continue;
        else
            return false;
    }
    for (int i = 0; i < 4; i++)
    {
        char old_one[4];
        char new_one[4];
        for (int j = 0; j < 4; j++)
            old_one[j] = tiles[j][i];
        int score = moveSingleLine(old_one, new_one);
        if (score == 0)
            continue;
        else
            return false;
    }
    return true;
}

int Board::GreedySolution()
{
    char temp[4][4];
    int score[4] = {0, 0, 0, 0};
    int max = 0;
    CopyTiles(tiles, temp);
    for (int i = 0; i < 4; i++)
    {
        score[i] = moveBoard((Direction)i);
        if (max < score[i])
            max = score[i];
        CopyTiles(temp, tiles);
    }
    if (max == 0)
        return moveBoard((Direction)(rand() % 4));
    else
        for (int i = 0; i < 4; i++)
            if (max == score[i])
            {
                max = moveBoard((Direction)i);
                break;
            }

    return max;
}

// the later copy the former
void Board::CopyTiles(char base[4][4], char copy[4][4])
{
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            copy[i][j] = base[i][j];
}

int Board::MonteCarloSolution()
{
    char temp[4][4];
    int score[4] = {0, 0, 0, 0};
    int max = 0;
    CopyTiles(tiles, temp);
    for (int i = 0; i < 100; i++)
    {
        score[0] += moveBoard(UP);
        score[0] += RandomDirectionToEnd();
        CopyTiles(temp, tiles);
    }
    max = score[0];
    for (int i = 0; i < 100; i++)
    {
        score[1] += moveBoard(DOWN);
        score[1] += RandomDirectionToEnd();
        CopyTiles(temp, tiles);
    }
    if (max < score[1])
        max = score[1];
    for (int i = 0; i < 100; i++)
    {
        score[2] += moveBoard(LEFT);
        score[2] += RandomDirectionToEnd();
        CopyTiles(temp, tiles);
    }
    if (max < score[2])
        max = score[2];
    for (int i = 0; i < 100; i++)
    {
        score[3] += moveBoard(RIGHT);
        score[3] += RandomDirectionToEnd();
        CopyTiles(temp, tiles);
    }
    if (max < score[3])
        max = score[3];
    if (max == score[0] && score[0] == score[1] && score[1] == score[2] && score[2] == score[3])
        return moveBoard((Direction)(rand() % 4));
    for (int i = 0; i < 4; i++)
        if (max == score[i])
            return moveBoard((Direction)i);
    return 0;
}

int Board::RandomDirectionToEnd()
{
    bool EndGame = checkGameOver();
    int score = 0;
    while (!EndGame)
    {
        score += moveBoard((Direction)(rand() % 4));
        EndGame = checkGameOver();
    }
    return score;
}