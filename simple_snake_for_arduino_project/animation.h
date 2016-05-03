#ifndef HEADER_ANIMATION_H
#define HEADER_ANIMATION_H

typedef struct screen_position {
	int row;
	int col;
};

typedef enum screen_side {
	TOP = 0, RIGHT, BOTTOM, LEFT
};

typedef enum animation_phase {
	FORWARD, BACKWARD
};


void change_side(screen_side &current_screen_side);

void change_animation_phase(animation_phase &phase);

void change_snake_shift(int &shift, animation_phase phase);

void manage_snake_animation(
	int** screen,
	int screen_size,
	int snake_start_length,
	int snake_growth_step_delay);

void change_side(screen_side &current_screen_side);

screen_position get_initial_position(
	int screen_dimension, 
	screen_side side, 
	int step);

int manage_side(
	int** square_screen, 
	int screen_dimension, 
	screen_side side, 
	int step, 
	int snake_to_draw, 
	int shift_to_draw);

void overflow_below_zero_subtraction(int &from, int &value);

void generate_image(
	int** square_screen,
	int screen_dimension,
	int snake_shift,
	int snake_length);

void clear_image(int** square_screen, int screen_dimension);

#endif