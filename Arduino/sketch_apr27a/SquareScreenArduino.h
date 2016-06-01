#include "LedControl.h"
#include "SquareScreen.h"

#ifndef HEADER_SQUARE_SCREEN_ARDUINO_H
#define HEADER_SQUARE_SCREEN_ARDUINO_H

class SquareScreenArduino : public SquareScreen {
protected:
  byte* screen;

  class MaxScreenSizeExeeded {};

  void prepare_pixel_for_arduino_screen(byte &x, byte &y)
  {
    // The arduino screen is mirrored
    // It would be OK if we look at it from underneath
    int temp = y;
    temp -= size / 2;
    y = -temp + size / 2 - 1;
  }
public:
  SquareScreenArduino(byte size);

  ~SquareScreenArduino();

  void print_screen();

  void clear_screen();
  
  void fire_all_diods();

  void set_pixel(byte x, byte y, byte value);

  byte get_pixel(byte x, byte y);
};

#endif
