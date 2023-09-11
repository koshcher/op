#include <iostream>
#include "lab1.h"
#include "lab2.h"
#include "shared.h"

void main()
{
    try {
        select({ {"Lab 1", lab1::run}, {"Lab 2", lab2::run} });
    }
    catch (...) {
        std::cout << "Unexpected error appeared";
    }
}