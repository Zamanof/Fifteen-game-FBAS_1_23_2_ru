#include"UI.h"
#include<string.h>
#include<conio.h>
#include"Enums.h"
#include"GameLogic.h"

using namespace std;



int main() {
	srand(time(NULL));
	short game_field[4][4]{};
	int choice{};
	unsigned char key{};
	const char* levelMenu[3]{
		"   Easy     ",
		"   Normal   ",
		"   Hard     "
	};

	const char* gameMenu[3]{
		"   Start new game     ",
		"   Load saved game    ",
		"   Exit               "
	};

	fill_game_fields(game_field);
	choice = menuChoice(gameMenu, 3);
	if (choice == 0) {
		choice = menuChoice(levelMenu, 3);
		start_position(game_field, choice);
	}
	else if (choice == 1) {
		loadFile(game_field);
	}
	else
	{
		return 0;
	}

	show_fields(game_field);

	while (!is_win(game_field))
	{
		key = _getch(); // 224
		key = _getch();
		move(game_field, key);
		system("cls");
		show_fields(game_field);

	}
	remove("game.dat");
	win_animation();
}


