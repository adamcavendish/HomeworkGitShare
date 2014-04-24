#include <omp.h>

#include <cstdio>
#include <cmath>

#include <complex>

int MandelbrotCalculate(const std::complex<double> & c, int maxiter) {
    std::complex<double> z = c;
    int n = 0;

    for(n = 0; n < maxiter; ++n) {
        if((std::abs(z) >= 2.0))
            break;
        z = z * z + c;
    }//for

    return n;
}


int main()
{
    const int width = 330, height = 200, num_pixels = width * height;

    const std::complex<double> center(-0.7, 0);
    const std::complex<double> span(2.7, -(4/3.0)* 2.7 * height/width);
    const std::complex<double> begin = center - span/2.0;
    //const std::complex<double> end = center + span/2.0;
    const int maxiter = 10000;

#ifndef NOPENMP
#   pragma omp parallel
    printf("Using OpenMP, thread num: %d\n", omp_get_num_threads());
#else
    printf("Calculating Without OpenMP\n");
#endif
    
    double start = 0, finish = 0;
    start = omp_get_wtime();

#ifndef NOPENMP
#   pragma omp parallel for ordered schedule(dynamic)
#endif
    for(int pix = 0; pix < num_pixels; ++pix) {
        const int x = pix % width, y = pix / width;
        std::complex<double> c = begin + std::complex<double>(x * span.real() / (width + 1.0),
                y * span.imag() / (height + 1.0));
        int n = MandelbrotCalculate(c, maxiter);
        if(n == maxiter)
            n = 0;

#ifndef NOPENMP
#       pragma omp ordered
#endif
        {
            if(n > 0) {
                static const char charset[] = ".,c8M@jawrpogOQEPGJ";
                char c = charset[n % (sizeof(charset) - 1)];
                putchar(c);
            } else {
                putchar(' ');
            }//if-else

            if(x == width - 1) {
                puts("|");
            }//if
        }
    }//for

    finish = omp_get_wtime();
    printf("duration: %lf\n", finish - start);

    return 0;
}

