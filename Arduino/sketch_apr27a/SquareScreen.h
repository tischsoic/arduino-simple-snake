#include "LedControl.h"
#ifndef HEADER_SQUARE_SCREEN_H
#define HEADER_SQUARE_SCREEN_H

class SquareScreen {
protected:
  byte size;

  class OutOfRangeException {};
public:
  SquareScreen(byte size)
  {
    this->size = size;
  }

  virtual ~SquareScreen() {};

  byte get_size()
  {
    return size;
  }

  virtual void print_screen() = 0;

  virtual void clear_screen() = 0;

  virtual void set_pixel(byte x, byte y, byte value) = 0;
};

#endif
