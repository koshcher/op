#ifndef LAB5
#define LAB5

#include <iostream>
#include "shared.h"

namespace lab5 {
struct CountResult {
    unsigned long operations;
    std::optional<unsigned long long> count;
};

/// <summary>
/// C = total! / (take! * (total - take)!)
/// </summary>
CountResult countSituationsLoop(const long& total, const long& take) {
    unsigned long long totalFactorial = 1;
    unsigned long long takeFactorial = 1;
    unsigned long long totalMinusTakeFactorial = 1;
    const long totalMinusTake = total - take;

    unsigned long iteration = 2;
    for (; iteration <= total; iteration += 1) {
        // Check for overflow of result
        if (totalFactorial > ULLONG_MAX / iteration) return { iteration - 1, std::nullopt };
        totalFactorial *= iteration;

        if (iteration <= take) takeFactorial = totalFactorial;
        if (iteration <= totalMinusTake) totalMinusTakeFactorial = totalFactorial;
    }

    return { iteration - 2,  totalFactorial / (takeFactorial * totalMinusTakeFactorial) };
}

CountResult calculateFactorialRecursively(const long& num) {
    if (num <= 1) return { 1, 1 };

    const auto prev = calculateFactorialRecursively(num - 1);
    if (!prev.count.has_value() || num > ULLONG_MAX / prev.count.value()) {
        return { prev.operations, std::nullopt };
    }

    return { prev.operations + 1, num * prev.count.value() };
}

CountResult countSituationsRecursive(const long& total, const long& take) {
    try {
        unsigned long operations = 0;

        const auto totalFactorial = calculateFactorialRecursively(total);
        operations += totalFactorial.operations;
        if (!totalFactorial.count.has_value()) {
            return { operations, std::nullopt };
        }

        const auto takeFactorial = calculateFactorialRecursively(take);
        operations += takeFactorial.operations;
        if (!takeFactorial.count.has_value()) {
            return { operations, std::nullopt };
        }

        const auto totalMinusTakeFactorial = calculateFactorialRecursively(total - take);
        operations += totalMinusTakeFactorial.operations;
        if (!totalMinusTakeFactorial.count.has_value()) {
            return { operations, std::nullopt };
        }

        const auto& total = totalFactorial.count.value();
        const auto& take = takeFactorial.count.value();
        const auto& totalMinusTake = totalMinusTakeFactorial.count.value();

        return {
            operations,
            total / (take * totalMinusTake)
        };
    }
    catch (...) {
        return { 0, std::nullopt };
    }
}

using CountSituationsStrategy = std::function<CountResult(const long&, const long&)>;

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
    if (!winningSituations.count.has_value()) {
        std::cout << "Number is too big to calculate with standard functionality" << std::endl;
        return;
    }
    const auto& winningSituationsCount = winningSituations.count.value();

    if (loosingCount < ticketsToTakeCount - 2) {
        std::cout << "Can't take only 2 winning" << std::endl;
    }
    else {
        const auto loosingSituations = strategy(loosingCount, ticketsToTakeCount - 2);
        if (!loosingSituations.count.has_value()) {
            std::cout
                << "Number is too big to calculate with standard functionality"
                << std::endl;
            return;
        }

        if (ULLONG_MAX / loosingSituations.count.value() < winningSituationsCount) {
            std::cout
                << "Number is too big to calculate with standard functionality"
                << std::endl;
            return;
        }
        const auto only2Winning = winningSituationsCount * loosingSituations.count.value();
        std::cout
            << "Situations when only 2 tickets are winning: "
            << only2Winning << std::endl;
        std::cout
            << "Operations count: "
            << winningSituations.operations + loosingSituations.operations << std::endl;
    }

    // at least 2 winning
    const auto takingSituations = strategy(totalTicketsCount - 2, ticketsToTakeCount - 2);
    if (!takingSituations.count.has_value()) {
        std::cout << "Number is too big to calculate with standard functionality" << std::endl;
        return;
    }

    if (ULLONG_MAX / takingSituations.count.value() < winningSituationsCount) {
        std::cout << "Number is too big to calculate with standard functionality" << std::endl;
        return;
    }
    const auto atLeast2Winning = winningSituationsCount * takingSituations.count.value();
    std::cout
        << "Situations when at least 2 tickets are winning: "
        << atLeast2Winning << std::endl;
    std::cout
        << "Operations count: "
        << winningSituations.operations + takingSituations.operations << std::endl;
}

void task1() {
    // m = count of winning tickets
    const long mCountOfItems = lround(shared::numFromConsole("Enter count of items (m): "));
    // n >= m
    const long nTotalTicketsCount = lround(
        shared::numFromConsole("Enter total count of tickets (n): ")
    );
    if (nTotalTicketsCount < mCountOfItems) {
        std::cout << "All tickets are winning" << std::endl;
        return;
    }

    const long kTicketsToTakeCount = lround(
        shared::numFromConsole("Enter count of tickets to take (k): ")
    );
    if (kTicketsToTakeCount > nTotalTicketsCount) {
        std::cout << "You can't take more tickets than exist." << std::endl;
    }

    std::cout << shared::LINE_SEPARATOR << std::endl;

    std::cout << "Loop strategy:" << std::endl;
    countSituations(
        countSituationsLoop, mCountOfItems,
        nTotalTicketsCount, kTicketsToTakeCount
    );

    std::cout << shared::LINE_SEPARATOR << std::endl;

    std::cout << "Recursive strategy:" << std::endl;
    countSituations(
        countSituationsRecursive, mCountOfItems,
        nTotalTicketsCount, kTicketsToTakeCount
    );

    std::cout << shared::LINE_SEPARATOR << std::endl;
}

struct ConsistencyItem {
    long num;
    long count;
};

ConsistencyItem showMonotonousConsistency(const long& count) {
    if (count <= 0) return { 1, 1 };

    auto item = showMonotonousConsistency(count - 1);
    if (item.num == item.count) {
        std::cout << item.num << " ";
        return { item.num + 1, 1 };
    }

    std::cout << item.num << " ";
    return { item.num, item.count + 1 };
}

void task2() {
    const long num = lround(shared::numFromConsole("Enter natural number (> 0): "));
    if (num <= 0) {
        std::cout << "Number " << num << " isn't natural." << std::endl;
        return;
    }

    showMonotonousConsistency(num);
    std::cout << std::endl;
}

void run() {
    std::cout << "Lab 5" << std::endl;

    shared::select({ {"Task 1", task1}, {"Task 2", task2} });

    std::cout << shared::LINE_SEPARATOR << std::endl;
}
}

#endif