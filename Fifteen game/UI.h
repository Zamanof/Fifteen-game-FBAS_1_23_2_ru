#pragma once
#include<Windows.h>
#include"Enums.h"
#include"HelperFunctions.h"
#include<iostream>
#include<iomanip>
#include<conio.h>

using namespace std;

void win_animation() {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	int backColor = BLACK;
	int foreColor = RED;
	WORD wcolor = ((backColor & 0x0f) << 4) + (foreColor & 0x0F);
	for (size_t i = 0; i < 15; i++)
	{
		system("cls");
		if (i % 2 == 0) {
			backColor = BLACK;
			foreColor = RED;
		}
		else {
			backColor = BLACK;
			foreColor = WHITE;
		}
		WORD wcolor = ((backColor & 0x0f) << 4) + (foreColor & 0x0F);
		SetConsoleTextAttribute(hConsole, wcolor);
		cout << "\t\t#     #     #   #    #    #\n";
		cout << "\t\t #   # #   #    #    # #  #\n";
		cout << "\t\t  # #   # #     #    #  # #\n";
		cout << "\t\t   #     #      #    #    #";
		Sleep(1000);
	}
	SetConsoleTextAttribute(hConsole, 15);
}

void show_fields(short fields[][4]) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	int backColor = BLACK;
	int foreColor = WHITE;
	WORD wcolor = ((backColor & 0x0f) << 4) + (foreColor & 0x0F);
	for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 4; j++)
		{
			if (is_right_postion(fields[i][j], i * 4 + j + 1)) {
				foreColor = GREEN;
			}
			else {
				foreColor = RED;
			}

			wcolor = ((backColor & 0x0f) << 4) + (foreColor & 0x0F);
			SetConsoleTextAttribute(hConsole, wcolor);
			if (fields[i][j] == 16) {
				cout << right << setw(4) << ' ';
			}
			else {
				cout << right << setw(4) << fields[i][j];
			}
		}
		cout << "\n\n";
	}
	foreColor = WHITE;
	wcolor = ((backColor & 0x0f) << 4) + (foreColor & 0x0F);
	SetConsoleTextAttribute(hConsole, wcolor);
}

int menuChoice(const char* Menu[], int length) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	int backColor = RED;
	int foreColor = WHITE;
	WORD wcolor{};
	unsigned char key{};
	int choice{};
	COORD coord{ 300, 500 };

	while (key != 13) {
		system("cls");
		for (size_t i = 0; i < length; i++)
		{
			if (choice == i) {
				/*cout << '>';*/
				backColor = RED;
			}
			else {
				/*cout << ' ';*/
				backColor = BLACK;
			}
			wcolor = ((backColor & 0x0f) << 4) + (foreColor & 0x0F);
			SetConsoleTextAttribute(hConsole, wcolor);
			SetConsoleCursorPosition(hConsole, coord);
			cout << Menu[i] << endl;
		}
		SetConsoleTextAttribute(hConsole, 15);
		key = _getch();
		if (key == 224) {
			key = _getch();
		}
		switch (key)
		{
		case UP:
			(--choice) %= length;
			if (choice < 0) choice = length - 1;
			break;
		case DOWN:
			(++choice) %= length;
			break;
		}
	}
	system("cls");
	return choice;
}