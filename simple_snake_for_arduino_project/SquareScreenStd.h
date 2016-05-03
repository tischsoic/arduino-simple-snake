#include "byte.h"
#include "SquareScreen.h"

#ifndef HEADER_SQUARE_SCREEN_STD_H
#define HEADER_SQUARE_SCREEN_STD_H

class SquareScreenStd : public SquareScreen {
protected:
	byte** screen;

public:
	SquareScreenStd(byte size);

	~SquareScreenStd();

	void print_screen();

	void clear_screen();

	void set_pixel(byte x, byte y, byte value);
};

#endif