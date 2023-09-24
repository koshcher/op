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
#include <vector>

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
}
```
