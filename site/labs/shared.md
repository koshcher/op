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
