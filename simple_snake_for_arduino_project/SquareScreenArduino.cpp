#include <iostream>
#include <string>

#include "SquareScreenArduino.h"

SquareScreenArduino::SquareScreenArduino(byte size)
	: SquareScreen(size)
{
	if (size > 8) {
		throw MaxScreenSizeExeeded();
	}

	if (size < 0) {
		throw OutOfRangeException();
	}

	screen = new byte[size];
}

SquareScreenArduino::~SquareScreenArduino()
{
	delete screen;
}

void SquareScreenArduino::print_screen()
{
	std::string separator = " ";

	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			std::cout << (int)get_pixel(i, j) << (j != size - 1 ? separator : "");
		}
		std::cout << std::endl;
	}
}

void SquareScreenArduino::clear_screen()
{
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			set_pixel(i, j, 0);
		}
	}
}

byte SquareScreenArduino::get_pixel(byte x, byte y)
{
	byte row = screen[x];
	return (row >> y) & 1;
}

void SquareScreenArduino::set_pixel(byte x, byte y, byte value)
{
	if (x < 0 || x >= size
		|| y < 0 || y >= size) {
		throw OutOfRangeException();
	}

	byte row = screen[x];
	screen[x] ^= (-value ^ row) & (1 << y);
}