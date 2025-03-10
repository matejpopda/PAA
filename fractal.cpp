
#include "fractal.h"

#include <algorithm>
#include <ranges>
#include <vector>
#include <thread>

void calcurate_fractal_singlethread(Color* result) {

	SettingsSingleton settings = SettingsSingleton::getInstance();

	Bounds bounds = settings.getBounds();

	for (int i = 0; i < CANVAS_SIZE_X; i++) {
		for (int j = 0; j < CANVAS_SIZE_Y; j++) {

			TypePrecision x, y;
			x = bounds.left_x + (i / static_cast<TypePrecision>(CANVAS_SIZE_X)) * (bounds.right_x - bounds.left_x);
			y = bounds.bottom_y + (j / static_cast<TypePrecision>(CANVAS_SIZE_Y)) * (bounds.top_y - bounds.bottom_y);
			
			Complex point = Complex{ x,y };
			
			result[i + CANVAS_SIZE_X*j] = calculate_point(point);


		}
	}

}


std::vector<int> range_from_to(int start, int end) {
	std::vector<int> x{};

	for (int i = 0; i < end; i++) {
		x.push_back(i);
	}
	return x;
}


static Color calculate_point(Complex point) {

	Complex c{};
	Complex z{};

	SettingsSingleton settings = SettingsSingleton::getInstance();

	if (settings.fractal_type == MANDELBROT) {
		c = point;
		z = settings.getParameter(); 
	}
	else if (settings.fractal_type == JULIA) {
		z = point;
		c = settings.getParameter();
	}

	for (int i = 0; i < settings.number_of_iterations; i++) {
		z = addComplex(squareComplex(z), c);
		if (absValueSquaredComplex(z) > settings.cut_off_value) {
			int interpolated_number_of_iterations = floor(i * 255.0 / settings.number_of_iterations);
			return calculate_color_from_iteration_count(i);
		}

	}



	return calculate_color_from_iteration_count(0);
}

static Color calculate_color_from_iteration_count(int i) {
	Color result{};

	result.red = i;
	result.green = i;
	result.blue = i;
	//result.alpha = 0;

	return result;
}


// MULTITHREADED IMPLEMENTATION BELLOW

void calcurate_fractal_multithread(Color* result) {



	SettingsSingleton settings = SettingsSingleton::getInstance();

	Bounds bounds = settings.getBounds();

	auto calculate_fractal = [&](int starting_index, int ending_index) {

		for (int k = starting_index; k < ending_index; k++) {

			int i = k % CANVAS_SIZE_X;
			int j = k / CANVAS_SIZE_X;

			TypePrecision x, y;
			x = bounds.left_x + (i / static_cast<TypePrecision>(CANVAS_SIZE_X)) * (bounds.right_x - bounds.left_x);
			y = bounds.bottom_y + (j / static_cast<TypePrecision>(CANVAS_SIZE_Y)) * (bounds.top_y - bounds.bottom_y);

			Complex point = Complex{ x,y };

			result[k] = calculate_point(point);

		}
	};

	//calculate_fractal(0, CANVAS_SIZE_X * CANVAS_SIZE_Y);

	
	int thread_count = NUMBER_OF_THREADS_FOR_MULTITHREADING;
	int total_length = CANVAS_SIZE_X * CANVAS_SIZE_Y;

	int length_one_thread = (total_length / thread_count) + 1;


	std::vector<std::thread> threads;

	for (int iterator = 0; iterator < total_length; iterator += length_one_thread) {
		std::thread cur_thread(calculate_fractal, iterator, std::min(iterator + length_one_thread, total_length));
		threads.push_back(std::move(cur_thread));
	}

	for (auto& thread : threads) {

		thread.join();
	}
	



}



void calcurate_fractal_openMP(Color* result) {

	SettingsSingleton settings = SettingsSingleton::getInstance();

	Bounds bounds = settings.getBounds();
	
	#pragma omp parallel for num_threads(NUMBER_OF_THREADS_FOR_MULTITHREADING)
	for (int i = 0; i < CANVAS_SIZE_X; i++) {
		for (int j = 0; j < CANVAS_SIZE_Y; j++) {

			TypePrecision x, y;
			x = bounds.left_x + (i / static_cast<TypePrecision>(CANVAS_SIZE_X)) * (bounds.right_x - bounds.left_x);
			y = bounds.bottom_y + (j / static_cast<TypePrecision>(CANVAS_SIZE_Y)) * (bounds.top_y - bounds.bottom_y);

			Complex point = Complex{ x,y };

			result[i + CANVAS_SIZE_X * j] = calculate_point(point);


		}
	}

}
