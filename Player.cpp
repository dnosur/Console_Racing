#include "Player.h"
#include <conio.h>
#include <fstream>

Player::Player()
{
    speed = 1;
    score = 0;

    std::fstream ff;

    ff.open("score.txt", std::ios::in | std::ios::out | std::ios::binary | std::ios::app);

    ff.read((char*)&bestScore, sizeof(bestScore));
    ff.close();
}

void Player::Die()
{
    die = true;
}

bool Player::SetPos(int**& field, int posX, int posY, const int width, const int height)
{

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (field[i][j] == 1) field[i][j] = 0;
        }
    }

    pos.X = posX;
    pos.Y = posY;

    posX -= 1;
    posY -= 1;

    for (int i = 0; i < CarModelHeight; i++) {
        for (int j = 0; j < CarModelWidth; j++) {
            if (playerModel[i][j] == 1 && field[posY + i][posX + j] > 1) {
                Die();
                return false;
            }
        }
    }

    for (int i = 0; i < CarModelHeight; i++) {
        for (int j = 0; j < CarModelWidth; j++) {
            if(playerModel[i][j] == 1) field[posY + i][posX + j] = 1;
        }
    }

    return true;
}

bool Player::IsDie()
{
    return die;
}

void Player::Controller(int**& field, const int width, const int height)
{
    int press = 0;

    while (!die) {
        press = _getch();

        switch (press)
        {
        case 75: { //Left
            if (pos.X != 3) {
                pos.X -= 3;
                SetPos(field, pos.X, pos.Y, width, height);
            }
            break;
        }
        case 77: { //Right
            if (pos.X != 6) {
                pos.X += 3;
                SetPos(field, pos.X, pos.Y, width, height);
            }
            break;
        }
        default:
            break;
        }
    }
}

int Player::GetScore()
{
    return score;
}

void Player::SubScore(const int s)
{
    score += s;
}

int Player::GetBestScore()
{
    return bestScore;
}
