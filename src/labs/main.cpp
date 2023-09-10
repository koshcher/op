#include <iostream>
#include "lab1.h"
#include "lab2.h"

void main()
{
    try {
        lab1::run();
        //lab2::run();
    }
    catch (...) {
        std::cout << "Unexpected error appeared";
    }
}