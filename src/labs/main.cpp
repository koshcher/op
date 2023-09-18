#include "lab1.h"
#include "lab2.h"
#include "lab3.h"
#include "shared.h"
#include <iostream>

int main() {
    try {
        std::cout << "Roman Koshchei (variant 15)" << std::endl;
        std::cout << "---------------------------" << std::endl;
        select({ { "Lab 1", lab1::run }, { "Lab 2", lab2::run }, {"Lab 3", lab3::run } });
    }
    catch (...) {
        std::cout << "Unexpected error appeared";
    }

    return 0;
}