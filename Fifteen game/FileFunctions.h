#pragma once
#include <iostream>
void saveFile(short game_field[][4]) {
	FILE* file;
	fopen_s(&file, "game.dat", "wb");
	fwrite((char*)game_field, sizeof(short), 16, file);
	fclose(file);
}

void loadFile(short game_field[][4]) {
	FILE* file;
	fopen_s(&file, "game.dat", "rb");
	fread((char*)game_field, sizeof(short), 16, file);
	fclose(file);
}
