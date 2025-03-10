#ifndef SETTINGSSINGLETON
#define SETTINGSSINGLETON

#include "defaults.h"
#include "utils.h"

enum FRACTAL_TYPES {
    MANDELBROT,
    JULIA,
    POLYNOMIAL,
    RATIONAL_FUNCTION
};

enum COMPUTATION_TYPES {
    SINGLE_THREAD,
    MULTIPLE_THREADS,
    OPM_THREADS,
    CUDA
};


class SettingsSingleton {

private: 
	SettingsSingleton();

public:
    static SettingsSingleton& getInstance() {
        static SettingsSingleton theInstance;
        return theInstance;
    }

    TypePrecision canvas_width;
    TypePrecision canvas_height;
    TypePrecision real_part_parameter;
    TypePrecision im_part_parameter;

    int number_of_iterations;

    FRACTAL_TYPES fractal_type;

    COMPUTATION_TYPES computation_type;

    TypePrecision cut_off_value;

    TypePrecision bound_left;
    TypePrecision bound_right;
    TypePrecision bound_up;
    TypePrecision bound_down;


    Bounds getBounds() const {
        Bounds x = Bounds{};
        x.bottom_y = bound_down;
        x.top_y = bound_up;
        x.left_x = bound_left;
        x.right_x = bound_right;
        return x;
    };

    Complex getParameter() {
        Complex x = Complex{ real_part_parameter ,im_part_parameter };
        return x;
    };

    bool redraw_on_next_input_poll;
};




#endif