#ifndef LAB5
#define LAB5

#include <iostream>
#include "shared.h"

namespace lab5 {
/// <summary>
/// C = total! / (take! * (total - take)!)
/// </summary>
std::optional<unsigned long long> countSituationsLoop(const long& total, const long& take) {
    unsigned long long totalFactorial = 1;
    unsigned long long takeFactorial = 1;
    unsigned long long totalMinusTakeFactorial = 1;
    const long totalMinusTake = total - take;

    for (long i = 2; i <= total; i += 1) {
        // Check for overflow of result
        if (totalFactorial > ULLONG_MAX / i) return std::nullopt;
        totalFactorial *= i;

        if (i <= take) takeFactorial = totalFactorial;
        if (i <= totalMinusTake) totalMinusTakeFactorial = totalFactorial;
    }

    return totalFactorial / (takeFactorial * totalMinusTakeFactorial);
}

std::optional<unsigned long long> calculateFactorialRecursively(const long& num) {
    if (num <= 1) return 1;

    const auto prev = calculateFactorialRecursively(num - 1);
    if (!prev.has_value()) return std::nullopt;
    if (num > ULLONG_MAX / prev.value()) return std::nullopt;

    return num * prev.value();
}

std::optional<unsigned long long> countSituationsRecursive(const long& total, const long& take) {
    try {
        const auto totalFactorial = calculateFactorialRecursively(total);
        if (!totalFactorial.has_value()) return std::nullopt;
        const auto takeFactorial = calculateFactorialRecursively(take);
        if (!takeFactorial.has_value()) return std::nullopt;
        const auto totalMinusTakeFactorial = calculateFactorialRecursively(total - take);
        if (!totalMinusTakeFactorial.has_value()) return std::nullopt;

        return totalFactorial.value() / (takeFactorial.value() * totalMinusTakeFactorial.value());
    }
    catch (...) {
        return std::nullopt;
    }
}

using CountSituationsStrategy = std::function<std::optional<unsigned long long>(const long&, const long&)>;

void countSituations(
    const CountSituationsStrategy& strategy,
    const long& countOfItems,
    const long& totalTicketsCount,
    const long& ticketsToTakeCount
) {
    const long winningCount = countOfItems;
    const long loosingCount = totalTicketsCount - countOfItems;

    // only 2 winning
    const auto winningSituations = strategy(winningCount, 2);
    if (!winningSituations.has_value()) {
        std::cout << "Number is too big to calculate with standard functionality" << std::endl;
        return;
    }
    if (loosingCount < ticketsToTakeCount - 2) {
        std::cout << "Can't take only 2 winning" << std::endl;
    }
    else {
        const auto loosingSituations = strategy(loosingCount, ticketsToTakeCount - 2);
        if (!loosingSituations.has_value()) {
            std::cout << "Number is too big to calculate with standard functionality" << std::endl;
            return;
        }

        if (ULLONG_MAX / loosingSituations.value() < winningSituations.value()) {
            std::cout << "Number is too big to calculate with standard functionality" << std::endl;
            return;
        }
        const unsigned long long only2Winning = winningSituations.value() * loosingSituations.value();
        std::cout << "Situations when only 2 tickets are winning: " << only2Winning << std::endl;
    }

    // at least 2 winning
    const auto takingSituations = strategy(totalTicketsCount - 2, ticketsToTakeCount - 2);
    if (!takingSituations.has_value()) {
        std::cout << "Number is too big to calculate with standard functionality" << std::endl;
        return;
    }

    if (ULLONG_MAX / takingSituations.value() < winningSituations.value()) {
        std::cout << "Number is too big to calculate with standard functionality" << std::endl;
        return;
    }
    const unsigned long long atLeast2Winning = winningSituations.value() * takingSituations.value();
    std::cout << "Situations when at least 2 tickets are winning: " << atLeast2Winning << std::endl;
}

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

    std::cout << shared::LINE_SEPARATOR << std::endl;

    std::cout << "Loop strategy:" << std::endl;
    countSituations(countSituationsLoop, mCountOfItems, nTotalTicketsCount, kTicketsToTakeCount);

    std::cout << shared::LINE_SEPARATOR << std::endl;

    std::cout << "Recursive strategy:" << std::endl;
    countSituations(countSituationsRecursive, mCountOfItems, nTotalTicketsCount, kTicketsToTakeCount);

    std::cout << shared::LINE_SEPARATOR << std::endl;
}

void task2() {
    std::cout << "Not implemented" << std::endl;
}

void run() {
    std::cout << "Lab 5" << std::endl;

    shared::select({ {"Task 1", task1}, {"Task 2", task2} });

    std::cout << shared::LINE_SEPARATOR << std::endl;
}
}

#endif