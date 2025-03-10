#ifndef FRACTALCPP
#define FRACTALCPP

#include "defaults.h"
#include "utils.h"
#include <array>
#include <cassert>
#include <memory>
#include "SettingsSingleton.h"

void  calcurate_fractal_singlethread(Color* frame);

void calcurate_fractal_multithread(Color* frame);

void calcurate_fractal_openMP(Color* frame);

Color calculate_point(Complex point);

Color calculate_color_from_iteration_count(int i);





#endif