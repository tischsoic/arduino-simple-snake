#include "LedControl.h"
#include "SquareScreen.h"

#ifndef HEADER_SQUARE_SCREEN_ARDUINO_H
#define HEADER_SQUARE_SCREEN_ARDUINO_H

class SquareScreenArduino : public SquareScreen {
protected:
  byte* screen;

  class MaxScreenSizeExeeded {};
public:
  SquareScreenArduino(byte size);

  ~SquareScreenArduino();

  void print_screen();

  void clear_screen();

  void set_pixel(byte x, byte y, byte value);

  byte get_pixel(byte x, byte y);
};

#endif
