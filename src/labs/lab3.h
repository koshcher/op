#pragma once

#include <iostream>
#include <sstream>
#include "shared.h"

namespace lab3 {
double fx(const long& k, const int& x, const long& kFactorial) {
    return (pow(-1, k) * (k + 1) * pow(x, k)) / kFactorial;
}

void showState(
  const int& x, const long& k, const double& internalSum, const double& externalSum
) {
    std::cout
        << "| " << x << " | " << shared::fillSpace(k, 15) << " | "
        << shared::fillSpace(internalSum, 15) << " | "
        << shared::fillSpace(externalSum, 15) << " |" << std::endl;
}

void run() {
    std::cout << "Lab 3" << std::endl;
    std::cout << shared::LINE_SEPARATOR << std::endl;

    const double accuracy = shared::numFromConsole("Enter calculation accuracy (number): ");

    std::cout
        << "|---|-----------------|-----------------|-----------------|"
        << std::endl;
    std::cout
        << "| x | k               | internal sum    | external sum    |"
        << std::endl;
    std::cout
        << "|---|-----------------|-----------------|-----------------|"
        << std::endl;

    double externalSum = 0;
    for (int x = 1; x <= 5; ++x) {
        double internalSum = 0;

        long factorial = 1;
        long k = 0;
        while (k <= accuracy) {
            const double value = fx(k, x, factorial);
            if (isinf(value)) break;

            const double newInternalSum = internalSum + value;
            if (isinf(newInternalSum)) break;

            internalSum = newInternalSum;
            externalSum += value;
            showState(x, k, internalSum, externalSum);
            k += 1;
            factorial *= k;
        }
    }

    std::cout
        << "|---|-----------------|-----------------|-----------------|"
        << std::endl;
}
}