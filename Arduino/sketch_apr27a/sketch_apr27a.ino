// Test
// Source: https://brainy-bits.com/tutorials/how-to-control-max7219-led-matrix/

#include "LedControl.h"
#include "animation.h"

LedControl lc=LedControl(12,11,10,2);  // Pins: DIN,CLK,CS, # of Display connected

unsigned long delayTime=100;  // Delay between Frames

byte my_pow(byte num, byte p)
{
  byte result = 1;

  for(int i = 0; i < p; ++i) {
    result *= num;
  }

  return result;
}

byte screen_row_to_byte(byte *row, int screen_size)
{
   byte row_as_byte= 0;

    for(int i = 0; i < screen_size; ++i)
    {
      if (row[i] == 1) {
        row_as_byte += my_pow(2, i);
      }
    }

   return row_as_byte;
}

// Put values in arrays
byte invader1a[] =
{
   B00011000,  // First frame of invader #1
   B00111100,
   B01111110,
   B11011011,
   B11111111,
   B00100100,
   B01011010,
   B10100101
};

byte invader1b[] =
{
  B00011000, // Second frame of invader #1
  B00111100,
  B01111110,
  B11011011,
  B11111111,
  B00100100,
  B01011010,
  B01000010
};


void setup_old()
{
  lc.shutdown(0,false);  // Wake up displays
  lc.setIntensity(0,5);  // Set intensity levels
  lc.clearDisplay(0);  // Clear Displays

}


//////////////////////////////////////////////////////////////////////////

const int screen_dimension = 8;
const int snake_length = 4;

void setup() 
{
  setup_old();
  
  byte** screen = create_screen(screen_dimension);
  clearImage(screen, screen_dimension);
  
  manage_snake_animation(screen, screen_dimension, 3, 5);

  delete_screen(screen, screen_dimension);
}


void change_animation_phase(animation_phase &phase)
{
  switch (phase) {
  case FORWARD:
    phase = BACKWARD;
    return;
  case BACKWARD:
    phase = FORWARD;
  }
}

void change_snake_shift(int &shift, animation_phase phase)
{
  switch (phase) {
  case FORWARD:
    ++shift;
    return;
  case BACKWARD:
    --shift;
  }
}

void manage_snake_animation(
  byte** screen, 
  int screen_size, 
  int snake_start_length, 
  int snake_growth_step_delay)
{
  int snake_head_position = 0;

  int screen_resolution = pow(screen_size, 2);

  int snake_shift = -3;
  int snake_length = snake_start_length;

  animation_phase phase = FORWARD;

  for (int time = 1; time <= 130; ++time) {
    if (time % snake_growth_step_delay == 0
      && snake_head_position > 0 
      && snake_head_position < screen_resolution) {
      ++snake_length;
    }

    change_snake_shift(snake_shift, phase);
    change_snake_shift(snake_head_position, phase);

    generate_image(screen, screen_size, snake_shift, snake_length);
    printScreen(screen, screen_size);

    if (time % screen_resolution == 0) {
      change_animation_phase(phase);
      snake_length = snake_start_length;
    }
  }
}


void change_side(screen_side &current_screen_side) 
{
  if (current_screen_side == left) {
    current_screen_side = top;
  }
  else {
    current_screen_side = (screen_side)(current_screen_side + 1);
  }
}


screen_position get_initial_position(int screen_dimension, screen_side side, int step)
{
  screen_position initial_position = { 0, 0 };
  int current_side_length = screen_dimension - (2 * step) - 1;

  switch (side)
  {
  case top:
    initial_position.row = step;
    initial_position.col = step;
    break;
  case right:
    initial_position.row = step;
    initial_position.col = screen_dimension - step - 1;
    break;
  case bottom:
    initial_position.row = screen_dimension - step - 1;
    initial_position.col = screen_dimension - step - 1;
    break;
  case left:
    initial_position.row = screen_dimension - step - 1;
    initial_position.col = step;
    break;
  }

  return initial_position;
}

int manage_side(byte** square_screen, int screen_dimension, screen_side side, int step, int snake_to_draw, int shift_to_draw)
{
  screen_position current_position = get_initial_position(screen_dimension, side, step);
  int current_side_length = screen_dimension - (2 * step) - 1;

  int i = 0;
  for (; i < current_side_length; ++i) {
    if (snake_to_draw == 0) {
      break;
    }

    square_screen[current_position.row][current_position.col] = shift_to_draw > 0 ? 0 : 1;

    switch (side)
    {
    case top:
      ++current_position.col;
      break;
    case right:
      ++current_position.row;
      break;
    case bottom:
      --current_position.col;
      break;
    case left:
      --current_position.row;
      break;
    }

    if (shift_to_draw > 0) {
      --shift_to_draw;
    }
    else {
      --snake_to_draw;
    }
  }

  return i;
}

void overflow_below_zero_subtraction(int &from, int &value)
{
  int overflow = 0;

  from -= value;
  
  if (from < 0) {
    overflow = -from;
    from = 0;
  }

  value = overflow;
}

void generate_image(
  byte** square_screen, 
  int screen_dimension, 
  int snake_shift, 
  int snake_length)
{
  int snake_to_draw = snake_shift < 0 ? snake_length + snake_shift : snake_length;
  int shift_to_draw = snake_shift < 0 ? 0 : snake_shift;

  int drawn = 0;

  screen_side current_side = top;

  int currentRow = 0,
    currentCol = 0;

  int steps_count = screen_dimension / 2;

  clearImage(square_screen, screen_dimension);
  for (int step = 0; step < steps_count; ++step) {
    if (snake_to_draw == 0) {
      break;
    }

    //for each side:
    for (int side_step = 0; side_step < 4; ++side_step) {
      if (snake_to_draw == 0) {
        break;
      }

      drawn = manage_side(
        square_screen,
        screen_dimension,
        current_side,
        step,
        snake_to_draw,
        shift_to_draw);

      overflow_below_zero_subtraction(shift_to_draw, drawn);
      overflow_below_zero_subtraction(snake_to_draw, drawn);

      change_side(current_side);
    }
  }
}

void clearImage(byte** square_screen, int screen_dimension)
{
  for (int i = 0; i < screen_dimension; ++i) {
    for (int j = 0; j < screen_dimension; ++j) {
      square_screen[i][j] = 0;
    }
  }
}

void printScreen(byte** square_screen, int screen_dimension)
{
  for (int i = 0; i < screen_dimension; ++i) {
    lc.setRow(0,i,screen_row_to_byte(square_screen[i], screen_dimension));
  }
  delay(delayTime);
}

byte** create_screen(int screen_size)
{
  byte** screen = new byte*[screen_size];
  for (int i = 0; i < screen_size; ++i) {
    screen[i] = new byte[screen_size];
  }

  return screen;
}

void delete_screen(byte** screen, int screen_size)
{
  for (int i = 0; i < screen_size; ++i) {
    delete screen[i];
  }
  delete screen;
}



////////////////////////////////////////////////////////////////





//  Take values in Arrays and Display them
void sinvader1a()
{
//  for (int i = 0; i < 8; i++)  
//  {
//    lc.setRow(0,i,invader1a[i]);
//  }
}

void sinvader1b()
{
//  for (int i = 0; i < 8; i++)
//  {
//    lc.setRow(0,i,invader1b[i]);
//  }
}

void loop()
{
//// Put #1 frame on both Display
//    sinvader1a();
//    delay(delayTime);
//
//// Put #2 frame on both Display
//    sinvader1b();
//    delay(delayTime);

}
