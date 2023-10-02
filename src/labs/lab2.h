#ifndef LAB2
#define LAB2

#include "shared.h"
#include <optional>
#include <iostream>
#include <math.h>

namespace lab2 {
enum ScalesPosition { Left, Same, Right };
/*
    compare weight of left coin and right coin
    represents operations of weighing on scales
*/
ScalesPosition weighOnScales(const double& coinLeft, const double& coinRight) {
    if (coinLeft == coinRight) return ScalesPosition::Same;
    if (coinLeft > coinRight) return ScalesPosition::Left;
    return ScalesPosition::Right;
}

// validating input
bool validInput(const double& coin1, const double& coin2, const double& coin3) {
    if ((coin1 == coin2 && coin3 > coin1)
      || (coin1 == coin3 && coin2 > coin1)
      || (coin2 == coin3 && coin1 > coin2)
      ) {
        std::cout << "Real coins should weight more than fake one." << std::endl;
        return false;
    }
    if (coin1 != coin2 && coin1 != coin3 && coin2 != coin3) {
        std::cout << "All coins have different weight, so we can't find real one."
            << std::endl
            << "At least 2 coins should have same weight." << std::endl;
        return false;
    }
    if (coin1 == coin2 && coin1 == coin3 && coin2 == coin3) {
        std::cout << "All coins have same weight. "
            << "So we can't differ real and fake ones." << std::endl;
        return false;
    }
    return true;
}

void task2() {
    std::cout
        << "One of coins is fake (less weight), other two are real (weight same)"
        << std::endl;

    const double coin1 = shared::numFromConsole("Enter weight of first coin: ");
    const double coin2 = shared::numFromConsole("Enter weight of second coin: ");
    const double coin3 = shared::numFromConsole("Enter weight of third coin: ");

    if (!validInput(coin1, coin2, coin3)) return;

    // only 1 weigh on scales is allowed by task
    const auto position = weighOnScales(coin1, coin2);
    if (position == ScalesPosition::Left) {
        std::cout << "Coin 2 is fake one." << std::endl;
    }
    else if (position == ScalesPosition::Right) {
        std::cout << "Coin 1 is fake one." << std::endl;
    }
    else {
        std::cout << "Coin 3 is fake one." << std::endl;
    }
}

std::optional<double> f(const double& x) {
    if (x == 0) return std::nullopt;

    if (x == 5) return x;
    if (x > 5) return 1 / pow(x, 2);
    if (x < 0) return 1 + pow(x, 3);
    return 1 - sqrt(pow(x, 3));
}

void task1() {
    const double x = shared::numFromConsole("Enter argument x: ");
    const auto result = f(x);

    if (!result.has_value()) {
        std::cout << "Function doesn't have solution" << std::endl;
        return;
    }

    if (isinf(result.value())) {
        std::cout << "Result of function is infinity" << std::endl;
        return;
    }

    std::cout << "Result of function: " << result.value() << std::endl;
}

void run() {
    std::cout << "Lab 2" << std::endl;
    std::cout << "-----------------------------------" << std::endl;
    shared::select({ { "Task 1", task1 }, { "Task 2", task2 } });
}
}

#endif