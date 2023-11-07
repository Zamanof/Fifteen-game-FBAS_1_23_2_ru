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
	return false;
}

void saveFileUsers(User* users, int& length) {

	FILE* file;
	fopen_s(&file, "length.dat", "wb");
	fwrite((char*)&length, sizeof(int), 1, file);
	fclose(file);

	fopen_s(&file, "game.dat", "wb");
	fwrite((char*)users, sizeof(User), length, file);
	fclose(file);
}

User* loadFileUsers(User* users, int& length) {

	FILE* file;
	fopen_s(&file, "length.dat", "rb");
	fread((char*)&length, sizeof(int), 1, file);
	fclose(file);
	
	User* tmp = new User[length];

	fopen_s(&file, "game.dat", "rb");
	fread((char*)tmp, sizeof(User), length, file);
	fclose(file);
	delete[] users;
	return tmp;
}

User* registration(char* name, char* surname, char* login, int age, User* users, int& length) {
	cout << name << endl;

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
bool login(char* login, char* pass, User* users, int length, User& user, int& index) {
	if (isUser) {
		for (size_t i = 0; i < length; i++)
		{
			if (strcmp(login, users[i].login) == 0 && strcmp(pass, users[i].password) == 0) {
				user = users[i];
				index = i;
				return true;
			}
		}
		return false;
	}
	return false;

}

int main() {

	User user;
	int length = 0;
	/*User* users = new User[length]{ {"Nadir", "Zamanov", "Admin", "P@ss1234", 43}};
	saveFileUsers(users, length);*/
	int index{};
	User* users{};
	users = loadFileUsers(users, length);
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
			if (login(user.login, user.password, users, length, user, index)) {
				fill_game_fields(users[index].game_field);
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
			strcpy_s(user.login, 20, "");
			check = registration(user.name, user.surname, user.login, user.age, users, length);
			if (check != nullptr) {
				users = check;
			}
			saveFileUsers(users, length);
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
		start_position(users[index].game_field, choice);
	}
	else if (choice == 1) {
	}
	else
	{
		return 0;
	}

	show_fields(users[index].game_field);

	while (!is_win(users[index].game_field))
	{
		key = _getch(); // 224
		key = _getch();
		move(users[index].game_field, key);
		saveFileUsers(users, length);
		system("cls");
		show_fields(users[index].game_field);

	}

	win_animation();
}


