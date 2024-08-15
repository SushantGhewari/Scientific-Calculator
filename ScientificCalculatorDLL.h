#ifndef SCIENTIFIC_CALCULATOR_DLL_H
#define SCIENTIFIC_CALCULATOR_DLL_H

#include <complex>

extern "C" __declspec(dllexport) double Sin(double angle);
extern "C" __declspec(dllexport) double Cos(double angle);
extern "C" __declspec(dllexport) double Tan(double angle);

extern "C" __declspec(dllexport) double Log(double value);
extern "C" __declspec(dllexport) double Log10(double value);
extern "C" __declspec(dllexport) double Exp(double value);
extern "C" __declspec(dllexport) double Power(double base, double exponent);

extern "C" __declspec(dllexport) std::complex<double> AddComplex(double real1, double imag1, double real2, double imag2);
extern "C" __declspec(dllexport) std::complex<double> MultiplyComplex(double real1, double imag1, double real2, double imag2);

extern "C" __declspec(dllexport) double Mean(const double* data, size_t size);
extern "C" __declspec(dllexport) double Median(double* data, size_t size);
extern "C" __declspec(dllexport) double StandardDeviation(const double* data, size_t size);

#endif // SCIENTIFIC_CALCULATOR_DLL_H
