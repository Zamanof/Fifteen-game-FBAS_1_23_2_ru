#pragma once
#include"HelperFunctions.h"
#include"Enums.h"
#include<iostream>
#include"FileFunctions.h"

using namespace std;
void fill_game_fields(short fields[][4]) {
	short n = 1;
	for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 4; j++)
		{
			fields[i][j] = n++;
		}
	}
}

void move(short fields[][4], unsigned char key) {
	short x{}, y{};
	find_empty_cell(fields, x, y);
	switch (key)
	{
	case UP:
		if (x < 3) {
			swap(fields[x][y], fields[x + 1][y]);
			x++;
		}
		break;
	case DOWN:
		if (x != 0) {
			swap(fields[x][y], fields[x - 1][y]);
			x--;
		}

		break;
	case LEFT:
		if (y < 3) {
			swap(fields[x][y], fields[x][y + 1]);
			y++;
		}
		break;
	case RIGHT:
		if (y != 0) {
			swap(fields[x][y], fields[x][y - 1]);
			y--;
		}
		break;
	}
	/*saveFile(fields);*/
}

void start_position(short fields[][4], const int level) {
	int side{};
	int levels[]{ 500, 1000, 1500 };
	int sides[]{ UP, DOWN, LEFT, RIGHT };
	for (size_t i = 0; i < levels[level]; i++)
	{
		side = rand() % 4;
		move(fields, sides[side]);
	}
}

bool is_win(short fields[][4]) {

	for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 4; j++)
		{
			if (!is_right_postion(fields[i][j], i * 4 + j + 1)) return false;
		}
	}

	return true;
}
