#include "SettingsSingleton.h"


SettingsSingleton::SettingsSingleton() {
	canvas_height = CANVAS_SIZE_Y;
	canvas_width = CANVAS_SIZE_X;

	fractal_type = MANDELBROT;

	real_part_parameter = 0;
	im_part_parameter = 0;

	computation_type = SINGLE_THREAD; 

	number_of_iterations = 255; 

	bound_up = 2;
	bound_down = -2;
	bound_left = -2;
	bound_right = 2; 

	cut_off_value = 4;


	redraw_on_next_input_poll = true; 
	
}