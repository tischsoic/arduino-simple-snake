#include "LedControl.h"
#include "SnakeAnimation.h"
#include "SquareScreen.h"

/**
 * Constructor of SnakeAnimation class.
 * \param screen Screen of type SquareScreen to draw to
 * \param snake_start_length snake start length
 * \param snake_growth_delay snake growth delay
 */
SnakeAnimation::SnakeAnimation(
  SquareScreen *screen,
  byte snake_start_length,
  byte snake_growth_delay)
{
  this->screen = screen;
  this->snake_start_length = snake_start_length;
  this->snake_growth_step_delay = snake_growth_delay;
}

/**
 * Changes animation phase - snake can go
 * forward or backward
 */
void SnakeAnimation::change_animation_phase()
{
  switch (current_animation_phase) {
  case FORWARD:
    current_animation_phase = BACKWARD;
    return;
  case BACKWARD:
    current_animation_phase = FORWARD;
  }
}

/**
 * Changes snake shift based on animation phase.
 * The greater shift the closer to the center
 * \param shift shift to be changed
 */
void SnakeAnimation::change_snake_shift(int &shift)
{
  switch (current_animation_phase) {
  case FORWARD:
    ++shift;
    return;
  case BACKWARD:
    --shift;
  }
}

/**
 * Manages whole animation
 */
void SnakeAnimation::manage_snake_animation()
{
  int snake_head_position = 0;

  int screen_resolution = pow(screen->get_size(), 2);

  int snake_shift = -snake_start_length;
  int snake_length = snake_start_length;

  current_animation_phase = FORWARD;

  for (int time = 1; ; ++time) {
    if (time % snake_growth_step_delay == 0
      && snake_head_position > 0
      && snake_head_position < screen_resolution) {
        // If we head has not already reached end,
        // we increase snake length and decrease it's
        // shift because it can only move forward 
        // by one step at a frame.
      ++snake_length;
      if (current_animation_phase == FORWARD) {
        --snake_shift;
      } else {
        //If we go backward
//        ++snake_shift;
      }
      
    }

    change_snake_shift(snake_shift);
    change_snake_shift(snake_head_position);

    generate_image(snake_shift, snake_length);

    screen->print_screen();

    if ((current_animation_phase == FORWARD && snake_shift == screen_resolution)
      || (current_animation_phase == BACKWARD && snake_shift == -snake_length)) {
      change_animation_phase();     // Snake can go forward or backward
      
      // If we change snake's movement direction
      // we have to reset some params:s
      snake_length = snake_start_length;
      if (current_animation_phase == FORWARD) {
        snake_shift = -snake_start_length;
        snake_head_position = 0;
        time = 1;
        screen->fire_all_diods();
      }

      screen->turn_by_180_degrees_right();
    }
  }
}

/**
 * Changes side. Side is used in algorithm drawing snake
 * on screen. Animation starts from top ang goes through
 * right and bottom to left. After this cycle we move
 * one level closer to center and repeat process until
 * we reach center.
 */
void SnakeAnimation::change_side()
{
  current_screen_side = current_screen_side == LEFT
    ? current_screen_side = TOP
    : (screen_side)(current_screen_side + 1);
}

/**
 * Returns initial position
 */
SnakeAnimation::screen_position SnakeAnimation::get_initial_position(int step)
{
  screen_position initial_position = { 0, 0 };
  byte screen_size = screen->get_size();
  int current_side_length = screen_size - (2 * step) - 1;

  switch (current_screen_side)
  {
  case TOP:
    initial_position.row = step;
    initial_position.col = step;
    break;
  case RIGHT:
    initial_position.row = step;
    initial_position.col = screen_size - step - 1;
    break;
  case BOTTOM:
    initial_position.row = screen_size - step - 1;
    initial_position.col = screen_size - step - 1;
    break;
  case LEFT:
    initial_position.row = screen_size - step - 1;
    initial_position.col = step;
    break;
  }

  return initial_position;
}

/**
 * Method managing one side of animation on screen
 */
int SnakeAnimation::manage_side(int step, int snake_to_draw, int shift_to_draw)
{
  screen_position current_position = get_initial_position(step);
  int current_side_length = screen->get_size() - (2 * step) - 1;

  int i = 0;
  for (; i < current_side_length; ++i) {
    if (snake_to_draw == 0) {
      break;
    }

    byte pixel_value = shift_to_draw > 0 ? 0 : 1;
    screen->set_pixel(current_position.row, current_position.col, pixel_value);

    switch (current_screen_side)
    {
    case TOP:
      ++current_position.col;
      break;
    case RIGHT:
      ++current_position.row;
      break;
    case BOTTOM:
      --current_position.col;
      break;
    case LEFT:
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

/**
 * Special method for managing "from" and "value" values
 * Keeps "from" value above or equal to zero. 
 */
void SnakeAnimation::overflow_below_zero_subtraction(int &from, int &value)
{
  int overflow = 0;

  from -= value;

  if (from < 0) {
    overflow = -from;
    from = 0;
  }

  value = overflow;
}

/**
 * Method drawing snake on screen.
 */
void SnakeAnimation::generate_image(
  int snake_shift,
  int snake_length)
{
  int snake_to_draw = snake_shift < 0 ? snake_length + snake_shift : snake_length;  // Count of snake elements to draw
  int shift_to_draw = snake_shift < 0 ? 0 : snake_shift;                            // Count of shift elements to draw

  int drawn = 0;      // Number of elements already drawn

  current_screen_side = TOP;

  int steps_count = screen->get_size() / 2;   // Number of steps in algorithm

  screen->clear_screen();
  for (int step = 0; step < steps_count; ++step) {
    if (snake_to_draw == 0) {
      break;    // If we have drawn everything, we leave
    }

    //for each side:
    for (int side_step = 0; side_step < 4; ++side_step) {
      if (snake_to_draw == 0) {
        break;
      }

      drawn = manage_side(
        step,
        snake_to_draw,
        shift_to_draw);

      overflow_below_zero_subtraction(shift_to_draw, drawn);
      overflow_below_zero_subtraction(snake_to_draw, drawn);

      change_side();
    }
  }
}
