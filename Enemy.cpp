#include "Enemy.h"
#include <iostream>

void Enemy::ClearField(int**& field)
{
	for (int i = 0; i < field_height; i++) {
		for (int j = 0; j < field_width; j++) {
			if (field[i][j] == id) field[i][j] = 0;
		}
	}
}

Enemy::Enemy()
{
	die = true;
}

Enemy::Enemy(int id, int x, int y, const int field_width, const int field_height)
{
	this->id = id;

	coord.X = x;
	coord.Y = y;

	die = false;

	this->field_width = field_width;
	this->field_height = field_height;
}

void Enemy::Update(int**& field, Player& player)
{
	coord.Y += 1;

	ClearField(field);

	int _y = coord.Y + 2;

	if (_y >= field_height && coord.Y - 1 < field_height) {
		_y = coord.Y - 1;

		for (int i = 0; _y < field_height && i < CarModelHeight; _y++) {

			for (int j = 0; j < CarModelWidth && j + coord.X - 1 < field_width; j++) {
				if (playerModel[i][j] == 1 && field[_y][j + coord.X - 1] != 1)
					field[_y][j + coord.X - 1] = id;
				if (field[_y][j + coord.X - 1] == 1)
					player.Die();
			}

			i++;
		}
	}
	else if (_y < field_height) {
		for (int i = CarModelHeight - 1; _y >= coord.Y - 1 && _y >= 0; _y--) {

			for (int j = 0; j < CarModelWidth && j + coord.X - 1 < field_width; j++) {
				if (playerModel[i][j] == 1 && field[_y][j + coord.X - 1] != 1) 
					field[_y][j + coord.X - 1] = id;
				if (field[_y][j + coord.X - 1] == 1)
					player.Die();
			}

			i--;
		}
	}
	
	if (coord.Y - 1 > 0 && coord.Y - 1 >= field_height) {
		player.SubScore(50);
		die = true;
	}
}

void Enemy::SetPos(int X, int Y)
{
	this->coord.X = X;
	this->coord.Y = Y;
	
	if (coord.X < field_width && coord.Y < field_height ) die = false;
}

bool Enemy::IsDie()
{
	return die;
}

int Enemy::GetId()
{
	return id;
}

coords Enemy::GetCoords()
{
	return coord;
}


