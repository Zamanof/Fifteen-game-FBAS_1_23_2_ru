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

bool isUser(User* users, User user, int length) {
	if (users != nullptr) {
		for (size_t i = 0; i < length; i++)
		{
			if (strcmp(user.login, users[i].login) == 0) {
				return true;
			}
		}
	}
	else {
		return false;
	}
}

User* registration(char* name, char* surname, char* login, int age, User* users, int& length) {
	generateLogin(name, surname, login, age);
	User user;
	strcpy_s(user.name, 20, name);
	strcpy_s(user.surname, 20, surname);
	strcpy_s(user.login, 20, login);
	user.age = age;
	if (!isUser(users, user, length))
	{
		cout << "Your login is " << user.login << endl;
		char pass[20];
		char confirm[20];
		char symbol{};
		int i = 0;
		cin.ignore();
		puts("Enter your password: ");
		do {
			symbol = _getch();
			pass[i++] = symbol;
			_putch('*');
		} while (symbol != 13 && i < 18);
		pass[i - 1] = '\0';
		puts("\nConfirm your password: ");
		symbol = 0;
		i = 0;
		do {
			symbol = _getch();
			confirm[i++] = symbol;
			_putch('*');
		} while (symbol != 13 && i < 18);
		confirm[i - 1] = '\0';
		cout << '\n';
		if (strcmp(pass, confirm) == 0)
		{
			strcpy_s(user.password, 20, pass);
		}
		else {
			puts("Incorrect password");
		}
		User* tmp = new User[length + 1];
		for (int i = 0; i < length; i++)
		{
			tmp[i] = users[i];
		}
		tmp[length] = user;
		delete[] users;
		length++;
		return tmp;
	}
	else {
		cout << "User already registered" << endl;
		return nullptr;
	}

}
bool login(char* login, char* pass, User* users, int length, User& user) {
	if (isUser) {
		for (size_t i = 0; i < length; i++)
		{
			if (strcmp(login, users[i].login) == 0 && pass == users[i].password) {
				user = users[i];
				return true;
			}
		}
	}
	return false;

}

int main() {
	User user;
	int length = 0;
	User* users = nullptr;
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
	bool exit = true;
	while (exit)
	{
		User* check{};
		char symbol = 0;
			int i = 0;
			char pass[20]{};
		choice = menuChoice(startMenu, 3);
		switch (choice)
		{
		case 0:
			puts("Enter login: ");
			gets_s(user.login, 20);
			puts("Enter password: ");
			
			do {
				symbol = _getch();
				pass[i++] = symbol;
				_putch('*');
			} while (symbol != 13 && i < 18);
			pass[i - 1] = '\0';
			strcpy_s(user.password, 20, pass);
			if (login(user.login, user.password, users, length, user)) {
				fill_game_fields(user.game_field);
				exit = false;
			}
			else {
				cout << "Incorrect login or password" << endl;
				system("pause");
			}
			break;
		case 1:

			puts("Enter name: ");
			gets_s(user.name, 20);
			puts("Enter last name: ");
			gets_s(user.surname, 20);
			puts("Enter your age: ");
			cin >> user.age;
			check = registration(user.name, user.surname, user.login, user.age, users, length);
			if (check != nullptr) {
				users = check;
			}
			break;
		case 2:
			return 0;
			break;
		}
		system("cls");
	}




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


