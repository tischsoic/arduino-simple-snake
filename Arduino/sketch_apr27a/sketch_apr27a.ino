#include "LedControl.h"
#include "SquareScreen.h"
#include "SquareScreenArduino.h"
#include "SnakeAnimation.h"
#include "LedControlSettings.h"

const int screen_dimension = 8;
const int snake_length = 4;

#define LENGTH 3
#define GROW_STEP 4 

void setup() 
{
  prepare_screen();
  
  SquareScreen *square_screen = new SquareScreenArduino(8);
  SnakeAnimation animation(square_screen, LENGTH, GROW_STEP);
  animation.manage_snake_animation();

  delete square_screen;
}

void loop()
{

}

