#include <iostream>
#include "lab1.h"
#include "lab2.h"

void main()
{
    try {
        lab2::run();
        // lab1::run();
    }
    catch (...) {
        std::cout << "Unexpected error appeared";
    }
}