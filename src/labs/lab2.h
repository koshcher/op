#pragma once

#include <math.h>
#include <iostream>
#include "shared.h"

namespace lab2 {
    /*
        111: 3 same, 0 different
        110: 2 same, 1 different
        123: 0 same, 3 different
    */
    int sameCount(const double& a, const double& b, const double& c) {
        if (a == b && a == c) { return 3; }
        if (a == b || a == c || b == c) { return 2; }
        return 0;
    }

    void task2() {
        const double a = numFromConsole("Enter first number: ");
        const double b = numFromConsole("Enter second number: ");
        const double c = numFromConsole("Enter third number: ");

        const int same = sameCount(a, b, c);
        const int different = 3 - same;

        std::cout 
            << "Count of same numbers: " << same 
            << "; Count of different numbers: " << different << std::endl;
    }

    double fx(const double& a, const double& b) {
        if (b == 0) { return pow(a, 2); }

        if (a <= 0) { return 1; }

        if (b > 0) { return pow(a, 3) / b; }
        return a / pow(b, 2);
    }

    void task1() {
        const double a = numFromConsole("Enter argument a: ");
        const double b = numFromConsole("Enter argument b: ");

        std::cout << "Result of function: " << fx(a, b) << std::endl;
    }

    void run() {
        std::cout << "Lab 2 by Roman Koshchei (variant 8)" << std::endl;
        std::cout << "-----------------------------------" << std::endl;
        task1();
        std::cout << "-----------------------------------" << std::endl;
        task2();
    }
}