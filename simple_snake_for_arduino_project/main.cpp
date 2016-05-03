#include <iostream>
#include <string>
#include <bitset>

#include "byte.h"
#include "SquareScreen.h"
#include "SquareScreenStd.h"
#include "SquareScreenArduino.h"
#include "SnakeAnimation.h"

const int screen_dimension = 8;
const int snake_length = 4;

int main() 
{
	//SquareScreen *square_screen = new SquareScreenStd(8);
	SquareScreen *square_screen = new SquareScreenArduino(8);
	SnakeAnimation animation(square_screen, 3, 4);
	animation.manage_snake_animation();

	int a;
	std::cin >> a;
}