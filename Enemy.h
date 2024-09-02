#pragma once

#include "CarModel.h"
#include "Player.h"

#include "Coords.h"

class Enemy
{
	coords coord;

	int field_width;
	int field_height;

	void ClearField(int**& field);

	int id;

	bool die;
public:
	Enemy();
	Enemy(int id, int x, int y, const int field_width, const int field_height);

	void Update(int**& field, Player& player);
	void SetPos(int X, int Y);

	bool IsDie();

	int GetId();

	coords GetCoords();
};

