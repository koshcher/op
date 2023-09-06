#include <iostream>
#include <optional>
#include <string>

const double PI = 3.141592653589793238463;

// small wrapper to avoid throwing errors
std::optional<float> parse_num(std::string str) {
    try { return std::stof(str); }
    catch (...) { return std::nullopt; }
}

float num_from_console(std::string message) {
    std::cout << message;
    std::string input;

    // optimistic input without error message
    std::getline(std::cin, input);
    std::optional<float> num = parse_num(input);

    while (!num.has_value())
    {
        std::cout << "Input isn't a number. " << message;
        std::getline(std::cin, input);
        num = parse_num(input);
    }
    return num.value();
}

// X = (1 - A) / (1 + A) + | (B - 2D) / C^2 |
void task_1() {
    std::cout << "Task 1: count X = (1 - A) / (1 + A) + | (B - 2D) / C^2 |" << std::endl;

    float a = num_from_console("Enter number A: ");
    float b = num_from_console("Enter number B: ");
    float c = num_from_console("Enter number C: ");
    float d = num_from_console("Enter number D: ");

    double x = (1.0 - a) / (1.0 + a) + abs((b - 2.0 * d) / pow(c, 2));
    std::cout << "X = " << x << std::endl;
}

void task_2() {
    std::cout << "Task 2: find the volume of the cone" << std::endl;

    float r = num_from_console("Radius of base: ");
    float h = num_from_console("Height: ");

    double v = (1.0 / 3.0) * PI * r * r * h;
    std::cout << "V = " << v << std::endl;
}

void main()
{
    try {
        std::cout << "Lab 1 by Roman Koshchei (variant 8)" << std::endl;
        std::cout << "-----------------------------------" << std::endl;

        task_1();

        std::cout << "-----------------------------------" << std::endl;

        task_2();
    }
    catch (...) {
        std::cout << "Unexpected error appeared";
    }
}