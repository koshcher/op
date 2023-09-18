#pragma once

#include "shared.h"
#include <iostream>

/*

I store all code in header files. Because:
- programs are small
- keep code in 1 place

I prefer keep it simple while I can.

*/

namespace lab1 {
const double E = 2.71828182845904523536;

void task1() {
    std::cout
        << "Task 1: count X = ((1 - A) * C * E^A)/((1 - B) * cos D)"
        << std::endl;

    const double a = numFromConsole("Enter number A: ");
    const double b = numFromConsole("Enter number B: ");
    const double c = numFromConsole("Enter number C: ");
    const double d = numFromConsole("Enter number D: ");

    const double x = ((1 - a) * c * pow(E, a)) / ((1 - b) * cos(d));
    if (std::isinf(x)) {
        std::cout << "Operation isn't correct." << std::endl;
        return;
    }
    std::cout << "X = " << x << std::endl;
}

void task2() {
    std::cout << "Task 2: find distance (S)" << std::endl;

    const double a = numFromConsole("Acceleration (a): ");
    const double t = numFromConsole("Time of movement (t): ");

    const double s = 0.5 * a * pow(t, 2);
    std::cout << "S = " << s << std::endl;
}

void run() {
    std::cout << "Lab 1" << std::endl;
    std::cout << "-----------------------------------" << std::endl;

    select({ { "Task 1", task1 }, { "Task 2", task2 } });
}
}