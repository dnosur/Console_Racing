#pragma once

#include "Coords.h";
#include "CarModel.h"

class Player
{
	coords pos;

	int speed;
	int score;
	int bestScore;

	bool die = false;
public: 

	Player();

	void Die();

	bool SetPos(int**& field, int posX, int posY, const int width, const int height);
	bool IsDie();

	void Controller(int**& field, const int width, const int height);

	int GetScore();
	void SubScore(const int s);

	int GetBestScore();
};

