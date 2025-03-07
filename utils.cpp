#include "utils.h"




Complex addComplex(Complex a, Complex b) {
	
	Complex result{};

	result.real = a.real + b.real;
	result.imaginary = a.imaginary + b.imaginary;

	return result;

};


Complex multiplyComplex(Complex a, Complex b) {

	Complex result{};

	result.real = a.real * b.real - a.imaginary * b.imaginary;
	result.imaginary = a.real*b.imaginary + a.imaginary*b.real;

	return result;


};


Complex squareComplex(Complex a) {
	return multiplyComplex(a, a);
};



TypePrecision absValueSquaredComplex(Complex a) {
	return a.real * a.real + a.imaginary * a.imaginary;

};



