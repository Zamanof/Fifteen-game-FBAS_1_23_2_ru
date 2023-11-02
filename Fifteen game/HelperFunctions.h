#pragma once

void find_empty_cell(short fields[][4], short& x, short& y) {
	for (short i = 0; i < 4; i++)
	{
		for (short j = 0; j < 4; j++)
		{
			if (fields[i][j] == 16) {
				x = i;
				y = j;
			}
		}
	}
}
bool is_right_postion(short value, short position_value) {
	if (value == position_value) return true;
	return false;
};
