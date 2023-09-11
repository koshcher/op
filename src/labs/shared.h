#pragma once

#include <optional>
#include <iostream>
#include <string>
#include <functional>
#include <vector>

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

void select(const std::vector<std::pair<std::string, std::function<void()>>>& options) {
    if (options.size() == 0) return;

    while (true)
    {
        std::cout << "Select option:" << std::endl;
        for (int i = 0; i < options.size(); ++i) {
            const auto& option = options[i];
            std::cout << "[" << i << "] " << option.first << std::endl;
        }
        std::cout << "[another] Exit" << std::endl;

        const double choise = numFromConsole("");
        if (choise < 0 || choise >= options.size()) break;

        const auto& option = options[choise];
        option.second();
        std::cout << "-----------------------------------" << std::endl;
    }
}