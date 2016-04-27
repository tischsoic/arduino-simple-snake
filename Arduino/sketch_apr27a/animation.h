void generate_image(
  byte** square_screen,
  int screen_dimension,
  int snake_shift,
  int snake_length);
void clearImage(byte** square_screen, int screen_dimension);
void printScreen(byte** square_screen, int screen_dimension);
void manage_snake_animation(
  byte** screen,
  int screen_size,
  int snake_start_length,
  int snake_growth_step_delay);

byte** create_screen(int screen_size);
void delete_screen(byte** screen, int screen_size);

typedef enum animation_phase {
  FORWARD, BACKWARD
};

void change_animation_phase(animation_phase &phase);

void change_snake_shift(int &shift, animation_phase phase);

typedef enum screen_side {
  top, right, bottom, left
};

void change_side(screen_side &current_screen_side);

struct screen_position {
  int row;
  int col;
};

screen_position get_initial_position(int screen_dimension, screen_side side, int step);

int manage_side(byte** square_screen, int screen_dimension, screen_side side, int step, int snake_to_draw, int shift_to_draw);

void overflow_below_zero_subtraction(int &from, int &value);
