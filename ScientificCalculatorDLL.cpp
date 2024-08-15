#include "ScientificCalculatorDLL.h"
#include <cmath>
#include <complex>
#include <vector>
#include <algorithm>
#include <numeric>

// Trigonometric functions
extern "C" __declspec(dllexport) double Sin(double angle) {
    return std::sin(angle);
}

extern "C" __declspec(dllexport) double Cos(double angle) {
    return std::cos(angle);
}

extern "C" __declspec(dllexport) double Tan(double angle) {
    return std::tan(angle);
}

// Logarithmic and Exponential functions
extern "C" __declspec(dllexport) double Log(double value) {
    if (value <= 0) throw std::invalid_argument("Logarithm of non-positive value is undefined.");
    return std::log(value);
}

extern "C" __declspec(dllexport) double Log10(double value) {
    if (value <= 0) throw std::invalid_argument("Logarithm of non-positive value is undefined.");
    return std::log10(value);
}

extern "C" __declspec(dllexport) double Exp(double value) {
    return std::exp(value);
}

extern "C" __declspec(dllexport) double Power(double base, double exponent) {
    return std::pow(base, exponent);
}

// Complex number operations
extern "C" __declspec(dllexport) std::complex<double> AddComplex(double real1, double imag1, double real2, double imag2) {
    std::complex<double> num1(real1, imag1);
    std::complex<double> num2(real2, imag2);
    return num1 + num2;
}

extern "C" __declspec(dllexport) std::complex<double> MultiplyComplex(double real1, double imag1, double real2, double imag2) {
    std::complex<double> num1(real1, imag1);
    std::complex<double> num2(real2, imag2);
    return num1 * num2;
}

// Statistical functions
extern "C" __declspec(dllexport) double Mean(const double* data, size_t size) {
    double sum = std::accumulate(data, data + size, 0.0);
    return sum / size;
}

extern "C" __declspec(dllexport) double Median(double* data, size_t size) {
    std::vector<double> vec(data, data + size);
    std::sort(vec.begin(), vec.end());
    size_t mid = size / 2;
    if (size % 2 == 0) {
        return (vec[mid - 1] + vec[mid]) / 2.0;
    } else {
        return vec[mid];
    }
}

extern "C" __declspec(dllexport) double StandardDeviation(const double* data, size_t size) {
    double mean = Mean(data, size);
    double sq_sum = std::inner_product(data, data + size, data, 0.0,
        std::plus<double>(), [mean](double a, double b) { return (a - mean) * (b - mean); });
    return std::sqrt(sq_sum / size);
}
