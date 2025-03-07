#ifndef UTILS
#define UTILS

#include "defaults.h"





struct Complex {
	TypePrecision real;
	TypePrecision imaginary;

	Complex(TypePrecision a, TypePrecision b) {
		real = a;
		imaginary = b;
	}

	Complex() {
		real = 0;
		imaginary = 0;
	}
};


Complex addComplex(Complex a, Complex b);
Complex multiplyComplex(Complex a, Complex b);
Complex squareComplex(Complex a);

TypePrecision absValueSquaredComplex(Complex a);



#endif