#include "SquareScreenArduino.h"
#include "LedControl.h"
#include "LedControlSettings.h"

/**
 * Constructor
 */
SquareScreenArduino::SquareScreenArduino(byte size)
  : SquareScreen(size)
{
  screen = new byte[size];
  clear_screen();
}

/**
 * Destructor
 */
SquareScreenArduino::~SquareScreenArduino()
{
  delete screen;
}

/**
 * Method printing screen on Arduino Led screen
 */
void SquareScreenArduino::print_screen()
{
  for (int i = 0; i < size; ++i) {
    lc.setRow(0,i,screen[i]);
  }
  delay(delayTime);
}

/**
 * Method clearing screen
 */
void SquareScreenArduino::clear_screen()
{
  for (int i = 0; i < size; ++i) {
    for (int j = 0; j < size; ++j) {
      set_pixel(i, j, 0);
    }
  }
}

void SquareScreenArduino::fire_all_diods()
{
  for (int i = 0; i < size; ++i) {
    for (int j = 0; j < size; ++j) {
      set_pixel(i, j, 1);
    }
  }

  print_screen();
}

/**
 * Gets pixel state
 */
byte SquareScreenArduino::get_pixel(byte x, byte y)
{
  byte row = screen[x];
  return (row >> y) & 1;
}

/**
 * Sets pixel
 */
void SquareScreenArduino::set_pixel(byte x, byte y, byte value)
{
  prepare_pixel_position(x, y);
  prepare_pixel_for_arduino_screen(x, y);
  
  byte row = screen[x];
  screen[x] ^= (-value ^ row) & (1 << y);
}
