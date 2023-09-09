#pragma once

#include <optional>
#include <iostream>
#include <string>

/*

Functions that can be used across different labs.

*/

// small wrapper to avoid throwing errors
std::optional<double> parseNum(std::string str) {
    try { return std::stod(str); }
    catch (...) { return std::nullopt; }
}

double numFromConsole(std::string message) {
    std::cout << message;
    std::string input;

    // optimistic input without error message
    std::getline(std::cin, input);
    std::optional<double> num = parseNum(input);

    while (!num.has_value())
    {
        std::cout << "Input isn't a number. " << message;
        std::getline(std::cin, input);
        num = parseNum(input);
    }
    return num.value();
}