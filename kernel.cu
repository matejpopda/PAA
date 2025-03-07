
#include "kernel.cuh"


__device__ int mandelbrot(TypePrecision x, TypePrecision y, TypePrecision pr, TypePrecision pi, int max_iter, TypePrecision cutoff) {
    TypePrecision zr = pr;
    TypePrecision zi = pi;

    TypePrecision cr = x;
    TypePrecision ci = y;
    int iter = 0;
    while (zr * zr + zi * zi <= cutoff && iter < max_iter) {
        TypePrecision temp = zr * zr - zi * zi + cr;
        zi = 2.0 * zr * zi + ci;
        zr = temp;
        iter++;
    }
    return iter;
}


__device__ int julia(TypePrecision x, TypePrecision y, TypePrecision pr, TypePrecision pi, int max_iter, TypePrecision cutoff) {

    TypePrecision zr = x;
    TypePrecision zi = y;

    TypePrecision cr = pr;
    TypePrecision ci = pi;
    int iter = 0;
    while (zr * zr + zi * zi <= cutoff && iter < max_iter) {
        TypePrecision temp = zr * zr - zi * zi + cr;
        zi = 2.0 * zr * zi + ci;
        zr = temp;
        iter++;
    }
    return iter;
}


__global__ void mandelbrot_kernel(Color* image,
    TypePrecision xMin, TypePrecision xMax, TypePrecision yMin, 
    TypePrecision yMax, int max_iter, TypePrecision cutoff, FRACTAL_TYPES frac_type, 
    TypePrecision par_r, TypePrecision par_i) 
{
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    int j = blockIdx.y * blockDim.y + threadIdx.y;

    if (i >= CANVAS_SIZE_X || j >= CANVAS_SIZE_Y) return;

    TypePrecision x0 = xMin + (xMax - xMin) * i / CANVAS_SIZE_X;
    TypePrecision y0 = yMin + (yMax - yMin) * j / CANVAS_SIZE_Y;

    int iter; 
    if (frac_type == MANDELBROT) {
        iter = mandelbrot(x0, y0, par_r, par_i, max_iter, cutoff);
    }
    else //frac_type == JULIA
    {
        iter = julia(x0, y0, par_r, par_i, max_iter, cutoff);
    }
    
    int color = (iter == max_iter) ? 0 : (255 * iter / max_iter);

    Color pixelColor{};
    pixelColor.red = color;
    pixelColor.green = color;
    pixelColor.blue = color;

    int idx = j * CANVAS_SIZE_X + i;
    image[idx] = pixelColor;
}


void calcurate_fractal_cuda(Color* frame) {
    Color* device_frame;

    SettingsSingleton settings = SettingsSingleton::getInstance();
    int max_iter = settings.number_of_iterations;
    Bounds bounds = settings.getBounds();
    size_t img_size = CANVAS_SIZE_X * CANVAS_SIZE_Y * sizeof(Color);


    cudaMalloc(&device_frame, img_size);

    dim3 blockSize(16, 16);
    dim3 gridSize((CANVAS_SIZE_X + blockSize.x - 1) / blockSize.x, (CANVAS_SIZE_Y + blockSize.y - 1) / blockSize.y);


    
#pragma warning( push )
#pragma warning( disable : E0029)
    // Linter error 
    mandelbrot_kernel <<<gridSize, blockSize >>> (device_frame, bounds.left_x,
        bounds.right_x, bounds.bottom_y, bounds.top_y,
        max_iter, settings.cut_off_value, settings.fractal_type, settings.real_part_parameter, settings.im_part_parameter);
#pragma warning( pop )

    cudaMemcpy(frame, device_frame, img_size, cudaMemcpyDeviceToHost);

    cudaFree(device_frame);

}




