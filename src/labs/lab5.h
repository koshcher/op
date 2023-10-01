#pragma once

#include "shared.h"
#include <iostream>

namespace lab5 {
void task1() {
    // m = count of winning tickets
    const long mCountOfItems = lround(shared::numFromConsole("Enter count of items (m): "));
    // n >= m
    const long nTotalTicketsCount = lround(shared::numFromConsole("Enter total count of tickets (n): "));
    if (nTotalTicketsCount < mCountOfItems) {
        std::cout << "All tickets are winning" << std::endl;
        return;
    }

    const long kTicketsToTakeCount = lround(shared::numFromConsole("Enter count of tickets to take (k): "));
    if (kTicketsToTakeCount > nTotalTicketsCount) {
        std::cout << "You can't take more tickets than exist." << std::endl;
    }
}

void task2() {}

void run() {
    std::cout << "Lab 5" << std::endl;

    shared::select({ {"Task 1", task1}, {"Task 2", task2} });

    std::cout << shared::LINE_SEPARATOR << std::endl;
}
}