#include"UI.h"
#include<string.h>
#include<conio.h>
#include"Enums.h"
#include"GameLogic.h"

using namespace std;

struct User
{
	char name[20];
	char surname[20];
	char login[20];
	char password[20];
	int age;
	short game_field[4][4]{};
};

void generateLogin(char* name, char* surname, char* login, int age) {
	char tmp[20];
	strcpy_s(tmp, name);
	_strupr_s(tmp, 20);
	strncpy_s(login, 20, tmp, 3);
	strcat_s(login, 20, "_");
	strncpy_s(tmp, 20, surname, 3);
	_strlwr_s(tmp, 20);
	strcat_s(login, 20, tmp);
	strcat_s(login, 20, "_");
	_itoa_s(age, tmp, 10);
	strcat_s(login, 20, tmp);
	strcat_s(login, 20, "_");
	char random[4]{};
	for (size_t i = 0; i < 3; i++)
	{
		random[i] = char(rand() % 10 + '0');
	}
	strcat_s(login, 20, random);
}

bool registration(char* name, char* surname, char* login, int age) {
	generateLogin(name, surname, login, age);

	return false;
}
bool login(char* login, char* pass) {
	return true;
}

int main() {
	User user;

	srand(time(NULL));
	short game_field[4][4]{};
	int choice{};
	unsigned char key{};
	bool isUser = false;
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

	const char* startMenu[3]{
		"   Sign in            ",
		"   Sign up            ",
		"   Exit               "
	};

	choice = menuChoice(startMenu, 3);

	switch (choice)
	{
	case 0:
		puts("Enter login: ");
		gets_s(user.login, 20);
		puts("Enter password: ");
		gets_s(user.password, 20);
		login(user.login, user.password);
		break;
	case 1:
		puts("Enter name: ");
		gets_s(user.name, 20);
		puts("Enter last name: ");
		gets_s(user.surname, 20);
		puts("Enter your age: ");
		cin >> user.age;
		isUser = registration(user.name, user.surname, user.login, user.age);
		if (!isUser) {
			cout << "Your login is " << user.login << endl;
			char pass[20];
			char confirm[20];
			char symbol{};
			int i = 0;
			cin.ignore();
			puts("Enter your password: ");
			 do{
				symbol = _getch();
				pass[i++] = symbol;
				_putch('*');
			 } while (symbol != 13 && i < 18);
			pass[i-1] = '\0';
			puts("\nConfirm your password: ");
			symbol = 0;
			i = 0;
			do{
				symbol = _getch();
				confirm[i++] = symbol;
				_putch('*');
			} while (symbol != 13 && i < 18);
			confirm[i-1] = '\0';
			cout << '\n';
			if (strcmp(pass, confirm) == 0)
			{
				strcpy_s(user.password, 20, pass);
			}
			else {
				puts("Incorrect password");
			}
		}
		else {
			puts("User is already registered");
		}
		break;
	case 2:
		return 0;
		break;
	}

	system("pause");
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

	win_animation();
}


