#pragma once

#include <iostream>
#include <thread>
#include <fstream>

#include "Player.h"
#include "Enemy.h"

#include "Color.h"
#include "functions.h"

class Track
{
	const int track_width = 10;
	const int track_height = 18;

	const int maxEnemyInField = 2;

	int freeSpace;

	int** field;

	Player player;
	Color color;

	Enemy enemy1;
	Enemy enemy2;
public: 
	Track();

	void Start();
	void Update();

	void GenerateEnemy(Enemy& enemy,Enemy& secondEnemy);

	void End();
};

