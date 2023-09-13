# Спільний код

Код, що може використовуватися у декількох лабораторних роботах.

## Select

Функція для вибору опції, яку потрібно запустити.
Наприклад, для вибору завдання, яке ми хочемо виконати: 1 або 2.

```cpp
#include <iostream>
#include <functional>
#include <vector>

void select(
  const std::vector<std::pair<std::string, std::function<void()>>>& options
) {
    if (options.size() == 0) return;

    // using true, because we need to break in the middle of loop
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
