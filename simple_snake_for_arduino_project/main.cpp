#include <iostream>
#include <string>
#include <bitset>

#include "byte.h"
#include "SquareScreen.h"
#include "SquareScreenStd.h"
#include "SnakeAnimation.h"

const int screen_dimension = 8;
const int snake_length = 4;

byte screen_row_to_byte(byte *row, int screen_size)
{
	byte row_as_byte = 0;

	for (int i = 0; i < screen_size; ++i)
	{
		if (row[i] == 1) {
			// TODO
			row_as_byte = 0;
		}
	}

	return row_as_byte;
}

int main() 
{
	SquareScreen *square_screen = new SquareScreenStd(8);
	SnakeAnimation animation(square_screen, 3, 4);
	animation.manage_snake_animation();

	int a;
	std::cin >> a;
}