#pragma once

#include <iostream>
#include <optional>
#include <string>

/*

I store all code in header files. Because:
- programs are small
- keep code in 1 place

I prefer keep it simple while I can.

*/

const double PI = 3.141592653589793238463;

// small wrapper to avoid throwing errors
std::optional<float> parseNum(std::string str) {
    try { return std::stof(str); }
    catch (...) { return std::nullopt; }
}

float numFromConsole(std::string message) {
    std::cout << message;
    std::string input;

    // optimistic input without error message
    std::getline(std::cin, input);
    std::optional<float> num = parseNum(input);

    while (!num.has_value())
    {
        std::cout << "Input isn't a number. " << message;
        std::getline(std::cin, input);
        num = parseNum(input);
    }
    return num.value();
}

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

void runLab1()
{
    try {
        std::cout << "Lab 1 by Roman Koshchei (variant 8)" << std::endl;
        std::cout << "-----------------------------------" << std::endl;

        task1();

        std::cout << "-----------------------------------" << std::endl;

        task2();
    }
    catch (...) {
        std::cout << "Unexpected error appeared";
    }
}