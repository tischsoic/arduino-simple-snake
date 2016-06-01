#include "LedControl.h"
#ifndef HEADER_SQUARE_SCREEN_H
#define HEADER_SQUARE_SCREEN_H

class SquareScreen {
protected:
  byte size;
  bool turned_by_180_degrees_right = false;

  class OutOfRangeException {};

  void prepare_pixel_position(byte &x, byte &y)
  {
    if (!turned_by_180_degrees_right) {
      return;
    }

    x = -(x - size + 1);
    y = -(y - size + 1);
  }
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

  void turn_by_180_degrees_right()
  {
    turned_by_180_degrees_right = !turned_by_180_degrees_right;
  }

  virtual void print_screen() = 0;

  virtual void clear_screen() = 0;

  virtual void fire_all_diods() = 0;

  virtual void set_pixel(byte x, byte y, byte value) = 0;
};

#endif
