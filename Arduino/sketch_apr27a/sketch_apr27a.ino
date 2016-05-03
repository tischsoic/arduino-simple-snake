// Test
// Source: https://brainy-bits.com/tutorials/how-to-control-max7219-led-matrix/

#include "LedControl.h"
#include "SquareScreen.h"
#include "SquareScreenArduino.h"
#include "SnakeAnimation.h"
#include "LedControlSettings.h"

const int screen_dimension = 8;
const int snake_length = 4;

void setup() 
{
  prepare_screen();
  
  SquareScreen *square_screen = new SquareScreenArduino(8);
  SnakeAnimation animation(square_screen, 3, 4);
  animation.manage_snake_animation();

//  lc.setRow(0,0,1);
//  delay(delayTime);

  delete square_screen;
}

void loop()
{

}

