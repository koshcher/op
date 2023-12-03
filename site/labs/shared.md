# Спільний код

Код, що може використовуватися у декількох лабораторних роботах.

[Файл зі спільним кодом](https://github.com/koshcher/op/blob/main/src/labs/shared.h)

## Main.cpp

Файл з функцією `main`.

```cpp
#include "lab1.h"
#include "lab2.h"
#include "lab3.h"
#include "lab4.h"
#include "shared.h"
#include <iostream>

int main() {
    try {
        std::cout << "Roman Koshchei (variant 15) IPZ-12" << std::endl;
        std::cout << "---------------------------" << std::endl;
        shared::select({ { "Lab 1", lab1::run }, { "Lab 2", lab2::run },
            {"Lab 3", lab3::run }, { "Lab 4", lab4::run} });
    }
    catch (...) {
        std::cout << "Unexpected error appeared";
    }

    return 0;
}
```

## Select

Функція для вибору опції, яку потрібно запустити.
Наприклад, для вибору завдання, яке ми хочемо виконати: 1 або 2.

```cpp
#include <iostream>
#include <functional>
#include <vector>

void select(
    const std::vector<std::pair<std::string, std::function<void()>>>& options) {
    if (options.size() == 0)
        return;

    // using true, because we need to break in the middle of loop
    while (true) {
        std::cout << "Select option:" << std::endl;
        for (int i = 0; i < options.size(); ++i) {
            const auto& option = options[i];
            std::cout << "[" << i << "] " << option.first << std::endl;
        }
        std::cout << "[another] Exit" << std::endl;

        const long choise = lround(numFromConsole(""));
        if (choise < 0 || choise >= options.size())
            break;

        const auto& option = options[choise];
        std::cout << LINE_SEPARATOR << std::endl;
        option.second();
    }
}
```

Приклад використання:

```cpp
void task1() {
    std::cout << "Running task 1" << std::endl;
}

void task2() {
    std::cout << "Running task 2" << std::endl;
}

void main() {
    select({ {"Task 1", task1}, {"Task 2", task2} });
}
```

## Увесь код з shared.h

```cpp
#pragma once

#include <functional>
#include <iostream>
#include <optional>
#include <string>
#include <sstream>
#include <vector>
#include <variant>

/*

Functions that can be used across different labs.

*/

namespace shared {
/// <summary> Euler's number: e </summary>
const double E = 2.71828182845904523536;
const std::string LINE_SEPARATOR = "-----------------------------------";

// small wrapper to avoid throwing errors
std::optional<double> parseNum(std::string str) {
    try {
        return std::stod(str);
    }
    catch (...) {
        return std::nullopt;
    }
}

double numFromConsole(std::string message) {
    std::cout << message;
    std::string input;

    // optimistic input without error message
    std::getline(std::cin, input);
    std::optional<double> num = parseNum(input);

    while (!num.has_value()) {
        std::cout << "Input isn't a number. " << message;
        std::getline(std::cin, input);
        num = parseNum(input);
    }
    return num.value();
}

char charFromConsole() {
    char c;
    std::cin.get(c);
    return c;
}

int intFromConsole(std::string message) {
    long num = lround(shared::numFromConsole(message));
    while (num > INT_MAX || num < INT_MIN) {
        std::cout
            << "Number is too large. Maximum allowed number is: " << INT_MAX
            << ". Minimum allowed number is: " << INT_MIN << std::endl;
        num = lround(shared::numFromConsole(message));
    }
    return static_cast<int>(num);
}

int positiveIntFromConsole(std::string message) {
    int num = intFromConsole(message);
    while (num <= 0) {
        std::cout << "Number must be positive (>0)" << std::endl;
        num = intFromConsole(message);
    }
    return num;
}

void select(
  const std::vector<std::pair<std::string, std::function<void()>>>& options) {
    if (options.size() == 0)
        return;

    // using true, because we need to break in the middle of loop
    while (true) {
        std::cout << "Select option:" << std::endl;
        for (int i = 0; i < options.size(); ++i) {
            const auto& option = options[i];
            std::cout << "[" << i << "] " << option.first << std::endl;
        }
        std::cout << "[another] Exit" << std::endl;

        const long choise = lround(numFromConsole(""));
        if (choise < 0 || choise >= options.size())
            break;

        const auto& option = options[choise];
        std::cout << LINE_SEPARATOR << std::endl;
        option.second();
    }
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

std::string fillSpace(const std::string& value, const int& size) {
    std::string str = to_string(value);
    while (str.size() < size) str += " ";
    return str;
}

/// <summary>
/// Calculates factorial of number. If factorial is too large
/// to put into unsigned long long, then it will return nullopt.
/// </summary>
std::optional<unsigned long long> factorial(const long& number) noexcept {
    unsigned long long result = 1;
    for (long i = 2; i <= number; i += 1) {
        // Check for overflow of result
        if (result > ULLONG_MAX / i) return std::nullopt;
        result *= i;
    }
    return result;
}

// STR
struct Str {
    std::unique_ptr<char[]> data;
    int length;
};

Str makeStr(const int& length) {
    Str str = Str { std::make_unique<char[]>(length), length };
    for (int i = 0; i < length; i += 1) {
        str.data[i] = '\0';
    }
    return str;
}

void expandStr(Str& str, const int& additionalLength) {
    Str newStr = makeStr(str.length + additionalLength);
    for (int i = 0; i < str.length; i += 1) {
        newStr.data[i] = str.data[i];
    }
    str = std::move(newStr);
}

// remove unused memory
void compressStr(Str& str) {
    if (str.length <= 1) return;

    int newLength = 1;
    for (int i = 0; i < str.length; i += 1) {
        if (str.data[i] == '\0') break;
        newLength += 1;
    }
    if (newLength == str.length) return;

    Str compressedStr = makeStr(newLength);
    for (int i = 0; i < newLength; i += 1) {
        compressedStr.data[i] = str.data[i];
    }
    str = std::move(compressedStr);
}

// -1 if char isn't found
int symbolIndex(const Str& str, const char& symbol) {
    for (int i = 0; i < str.length; i += 1) {
        const auto& c = str.data[i];
        if (c == '\0') break;
        if (c == symbol) return i;
    }
    return -1;
}

void printlnStr(const Str& str) {
    for (int i = 0; i < str.length; ++i) {
        const auto& symbol = str.data[i];
        if (symbol == '\0') break;
        std::cout << symbol;
    }
    std::cout << std::endl;
}

void printStr(const Str& str) {
    for (int i = 0; i < str.length; ++i) {
        const auto& symbol = str.data[i];
        if (symbol == '\0') break;
        std::cout << symbol;
    }
}

void printStr(const Str& str, const int& lineSize) {
    for (int i = 0; i < str.length; ++i) {
        const auto& symbol = str.data[i];
        if (symbol == '\0') break;
        std::cout << symbol;
    }
    for (int i = 0; i < (lineSize - str.length - 1); i += 1) {
        std::cout << " ";
    }
}

const int BUFFER_SIZE = 256;

Str enterString() {
    Str str = makeStr(BUFFER_SIZE);

    char symbol;
    int index = 0;

    while (std::cin.get(symbol) && symbol != '\n') {
        // last symbol mast remaint \0
        if (index >= str.length - 1) {
            expandStr(str, BUFFER_SIZE);
        }

        str.data[index] = symbol;
        index += 1;
    }
    compressStr(str);
    return str;
}

Str copyStr(const Str& str) {
    Str newStr = makeStr(str.length);
    for (int i = 0; i < str.length; i += 1) {
        newStr.data[i] = str.data[i];
    }
    return newStr;
}

bool areStrEquar(const Str& str1, const Str& str2) {
    if (str1.length != str2.length) return false;

    for (int i = 0; i < str1.length; i += 1) {
        if (str1.data[i] != str2.data[i]) return false;
    }
    return true;
}

// VARIANT

// from https://stackoverflow.com/questions/64017982/c-equivalent-of-rust-enums

template<class... Ts> struct overloaded: Ts... { using Ts::operator()...; };
// explicit deduction guide (not needed as of C++20)
template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;

template <typename Val, typename... Ts>
auto match(const Val& val, Ts... ts) {
    return std::visit(overloaded { ts... }, val);
}
}
```
