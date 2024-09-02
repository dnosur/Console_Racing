#include "functions.h"

void clear() {
	system("cls");
}

void pause() {
	_getch();
}

void gotoxy(int X, int Y)
{
	COORD coord = { X, Y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void lower_string(std::string& str)
{
	for (int i = 0; str[i] != '\0'; i++)
	{
		if (str[i] >= 'A' && str[i] <= 'Z') {
			str[i] = str[i] + 32;
		}
	}
}