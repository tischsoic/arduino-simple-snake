#include "LedControl.h"
#include "SquareScreen.h"

#ifndef HEADER_SNAKE_ANIMATION_H
#define HEADER_SNAKE_ANIMATION_H

class SnakeAnimation {
public:
  SnakeAnimation(
    SquareScreen *screen,
    byte snake_start_length,
    byte snake_growth_step_delay);

  ~SnakeAnimation() {};

  void manage_snake_animation();
private:
  typedef struct screen_position {
    byte row;
    byte col;
  };

  typedef enum screen_side {
    TOP = 0, RIGHT, BOTTOM, LEFT
  };

  typedef enum animation_phase {
    FORWARD, BACKWARD
  };

  SquareScreen *screen;
  byte snake_start_length;
  byte snake_growth_step_delay;

  screen_side current_screen_side;
  animation_phase current_animation_phase;
  screen_position current_screen_position;


  void change_side();

  void change_animation_phase();

  void change_snake_shift(int &shift);

  screen_position get_initial_position(int step);

  int manage_side(
    int step,
    int snake_to_draw,
    int shift_to_draw);

  void overflow_below_zero_subtraction(int &from, int &value);

  void generate_image(
    int snake_shift,
    int snake_length);
};


#endif
