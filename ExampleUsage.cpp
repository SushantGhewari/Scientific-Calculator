#include <iostream>
#include "ScientificCalculatorDLL.h"
#include "DatabaseUtils.h"

int main() {
    // Example usage of mathematical functions
    double angle = 1.0;
    std::cout << "Sin(" << angle << ") = " << Sin(angle) << std::endl;

    double value = 10.0;
    std::cout << "Log(" << value << ") = " << Log(value) << std::endl;

    // Example usage of complex number functions
    auto complexSum = AddComplex(1.0, 2.0, 3.0, 4.0);
    std::cout << "Complex Sum: " << complexSum << std::endl;

    // Logging a calculation
    LogCalculation("Sin(1.0)", std::to_string(Sin(1.0)));

    // Managing history
    ManageHistory(100);  // Keep only the last 100 entries

    return 0;
}
