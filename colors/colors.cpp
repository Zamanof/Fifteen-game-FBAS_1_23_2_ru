#include<iostream>
#include<Windows.h>
#include<iomanip>

using namespace std;

enum colors
{
	BLACK,
	BLUE,
	GREEN,
	AQUA,
	RED,
	PURPLE,
	YELLOW,
	WHITE,
	GRAY,
	LIGHT_BLUE,
	LIGHT_GREEN,
	LIGHT_AQUA,
	LIGHT_RED,
	LIGHT_PURPLE,
	LIGHT_YELLOW,
	BRIGHT_WHITE
};

int main() {
	/*system("color f0");
	cout << "Hello" << endl;
	system("color 69");
	cout << "Hello" << endl;*/
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	/*for (size_t i = 0; i <= 256; i++)
	{
		SetConsoleTextAttribute(hConsole, i);
		cout << setw(5) << i;
		if ((i+1) % 16 == 0 && i != 0) cout << '\n';
	}
	SetConsoleTextAttribute(hConsole, 15);*/
	int backColor = WHITE;
	int foreColor = RED;
	WORD wcolor = ((backColor & 0x0f) << 4) + (foreColor & 0x0F);
	

	SetConsoleTextAttribute(hConsole, wcolor);
	cout << "Hello" << endl;
}