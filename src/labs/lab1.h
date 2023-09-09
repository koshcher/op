#pragma once

#include <iostream>
#include "shared.h"

/*

I store all code in header files. Because:
- programs are small
- keep code in 1 place

I prefer keep it simple while I can.

*/

namespace lab1 {
    const double PI = 3.141592653589793238463;

    // X = (1 - A) / (1 + A) + | (B - 2D) / C^2 |
    void task1() {
        std::cout << "Task 1: count X = (1 - A) / (1 + A) + |(B - 2D) / C^2|" << std::endl;

        float a = numFromConsole("Enter number A: ");
        float b = numFromConsole("Enter number B: ");
        float c = numFromConsole("Enter number C: ");
        float d = numFromConsole("Enter number D: ");

        double x = (1.0 - a) / (1.0 + a) + abs((b - 2.0 * d) / pow(c, 2));
        std::cout << "X = " << x << std::endl;
    }

    void task2() {
        std::cout << "Task 2: find the volume of the cone" << std::endl;

        float r = numFromConsole("Radius of base: ");
        float h = numFromConsole("Height: ");

        double v = (1.0 / 3.0) * PI * r * r * h;
        std::cout << "V = " << v << std::endl;
    }

    void run()
    {
        std::cout << "Lab 1 by Roman Koshchei (variant 8)" << std::endl;
        std::cout << "-----------------------------------" << std::endl;

        task1();

        std::cout << "-----------------------------------" << std::endl;

        task2();
    }
}