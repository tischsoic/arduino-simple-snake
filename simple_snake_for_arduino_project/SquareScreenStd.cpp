#include <iostream>
#include <string>

#include "SquareScreenStd.h"

SquareScreenStd::SquareScreenStd(byte size)
	: SquareScreen(size)
{
	this->size = size;
	screen = new byte*[size];

	for (int i = 0; i < size; ++i) {
		screen[i] = new byte[size];
	}
}

SquareScreenStd::~SquareScreenStd()
{
	for (byte i = 0; i < size; ++i) {
		delete screen[i];
	}
	delete screen;
}

void SquareScreenStd::print_screen()
{
	std::string separator = " ";

	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			std::cout << (int)screen[i][j] << (j != size - 1 ? separator : "");
		}
		std::cout << std::endl;
	}
}

void SquareScreenStd::clear_screen()
{
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			screen[i][j] = 0;
		}
	}
}

void SquareScreenStd::set_pixel(byte x, byte y, byte value)
{
	if (x < 0 || x >= size
		|| y < 0 || y >= size) {
		throw OutOfRangeException();
	}

	screen[x][y] = value;
}