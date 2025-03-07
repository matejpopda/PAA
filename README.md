Small fractal viewer written in C++ and CUDA. Created as a project for the "Paralell Algorithms and Architectures" class. 

# Controls
- WASD - Panning
- Q/Z - Zoom in/out
- Shift - Holding it while pressing previous keys makes it so you can make finer adjustments.
- Space - Redraw the canvas (useful for measuring performance)

Otherwise you can use  your mouse to toggle options in the settings window. 
- Type of fractal selects which fractal is drawn.
  - Mandelbrot set
      - The recursive formula in complex plane to compute Mandelbrot set is given by:
        ![equation](https://latex.codecogs.com/svg.image?&space;z\mapsto&space;z^2&plus;c&space;)
        where z is a point in the complex plane and c is a constant parameter.
  - Julia set
    - Julia set is given by the same recursive formula, with the change that c is a point in the complex plane and z_0 is a constant parameter.  
- Type of computation selects which method is used.
  - SingleThread - Computes the fractal on the CPU using one thread.
  - MultiThread - Computes the fractal on the CPU using multiple threads. (Default is 16 software threads, can be adjusted in the `default.h` header)
  - Cuda - Computes the fractal on the GPU using CUDA
- Number of iterations
- Cut-off value - when |z|^2 exceeds this value, we assume that further iteration diverges. It is proven that standard Mandelbrot set 4 is enough.
- The sliders can be used to turn the constant parameter for either of the fractals.

Settings in `default.h` 
  - In the header you can change the size of the canvas window, or the controls window.
  - You can also change what Type is used for floating point operations (float, double, long double)


# Performance graphs

Time is in miliseconds. At the bottom we see how many iterations we were making. We were testing the performance using default settings without panning the
view.


![image](https://github.com/user-attachments/assets/16b173f7-a05e-4010-85ad-6758bbc9aee5)

![image](https://github.com/user-attachments/assets/029974bb-b316-4989-ba3b-bcd584cd486d)

![image](https://github.com/user-attachments/assets/597a26ff-baba-4498-93b5-c81e66904083)


