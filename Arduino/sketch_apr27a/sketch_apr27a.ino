// Test
// Source: https://brainy-bits.com/tutorials/how-to-control-max7219-led-matrix/

#include "LedControl.h"
#include "SquareScreen.h"
#include "SquareScreenArduino.h"
#include "SnakeAnimation.h"

LedControl lc=LedControl(12,11,10,2);  // Pins: DIN,CLK,CS, # of Display connected

unsigned long delayTime=100;  // Delay between Frames

const int screen_dimension = 8;
const int snake_length = 4;

void setup() 
{
  SquareScreen *square_screen = new SquareScreenArduino(8);
  SnakeAnimation animation(square_screen, 3, 4);
  animation.manage_snake_animation();

  lc.setRow(0,0,1);
  delay(delayTime);

  delete square_screen;
}

void loop()
{

}

