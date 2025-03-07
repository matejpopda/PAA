#ifndef CUDA_H
#define CUDA_H

#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <stdio.h>

#include "defaults.h"
#include "SettingsSingleton.h"



void  calcurate_fractal_cuda(Color* frame);


#endif 