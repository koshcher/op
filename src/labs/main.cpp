#include "lab1.h"
#include "lab2.h"
#include "lab3.h"
#include "lab4.h"
#include "lab5.h"
#include "lab6.h"
#include "shared.h"
#include <iostream>

int plus(int a, int b) {
    return a + b;
}

int main() {
    try {
        std::cout << "Roman Koshchei (variant 15) IPZ-12" << std::endl;
        std::cout << "---------------------------" << std::endl;
        shared::select({
            { "Lab 1", lab1::run }, { "Lab 2", lab2::run }, { "Lab 3", lab3::run },
            { "Lab 4", lab4::run }, { "Lab 5", lab5::run }, { "Lab 6", lab6::run }
        });
    }
    catch (...) {
        std::cout << "Unexpected error appeared";
    }

    return 0;
}