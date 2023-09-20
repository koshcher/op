#pragma once

#include <iostream>
#include <sstream>
#include "shared.h"

namespace lab3 {
long factorial(const long& n) {
    long num = 1;
    for (long i = 1; i <= n; ++i) num *= i;
    return num;
}

double fx(const long& k, const int& x) {
    return (pow(-1, k) * (k + 1) * pow(x, k)) / factorial(k);
}

template <typename T>
std::string to_string(T const& value) {
    std::stringstream sstr;
    sstr << value;
    return sstr.str();
}

std::string fillSpace(const double& value, const int& size) {
    std::string str = to_string(value);
    if (value >= 0) str = " " + str;
    while (str.size() < size) str += " ";
    return str;
}

void showState(
    const int& x, const long& k, const double& internalSum, const double& externalSum
) {
    std::cout
        << "| " << x << " | " << fillSpace(k, 15) << " | "
        << fillSpace(internalSum, 15) << " | "
        << fillSpace(externalSum, 15) << " |" << std::endl;
}

void run() {
    std::cout << "Lab 3" << std::endl;
    std::cout << LINE_SEPARATOR << std::endl;

    const double accuracy = numFromConsole("Enter calculation accuracy (number): ");

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
        long k = 0;
        while (k <= accuracy) {
            const double value = fx(k, x);
            if (isinf(value)) break;

            const double newInternalSum = internalSum + value;
            if (isinf(newInternalSum)) break;

            internalSum = newInternalSum;
            showState(x, k, internalSum, externalSum);
            k += 1;
        }

        externalSum += internalSum;
        showState(x, k - 1, internalSum, externalSum);
    }

    std::cout
        << "|---|-----------------|-----------------|-----------------|"
        << std::endl;
}
}