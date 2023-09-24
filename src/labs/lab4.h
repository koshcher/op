#pragma once

#include <iostream>
#include "shared.h"

namespace lab4 {
/// <summary> e^x = 1 + x^1 / 1! + x^2 / 2! + ... </summary>
/// <param name="accuracy"> Recommended from 10^-2 to 10^-6 </param>
double exponentialTaylorExpansion(const double& x, const double& accuracy) {
    double sum = 1;
    double element = 1;
    for (int i = 1; fabs(element) > accuracy; i += 1) {
        element = element * (x / i);
        if (isinf(element)) break;
        sum += element;
    }
    return sum;
}

/// <summary>
/// Count precision: number of symbors after point.
/// Just keep multiplying by 10 number until it has no more numbers after point.
/// </summary>
int calculatePrecision(double number) {
    int precision = 0;
    while (number != floor(number)) {
        precision += 1;
        number *= 10;
    }
    return precision;
}

double roundToPrecision(const double& value, const int& precision) {
    const double factor = pow(10, precision);
    const double result = round(value * factor) / factor;
    return result;
}

void showNoSolution(const double& x) {
    std::cout << "| " << shared::fillSpace(x, 15) << " | "
        << shared::fillSpace(" no solution", 51) << " |" << std::endl;
}

void showState(double& x, const double& y, const double& standard, const double& error) {
    std::cout
        << "| " << shared::fillSpace(x, 15) << " | "
        << shared::fillSpace(y, 15) << " | "
        << shared::fillSpace(standard, 15) << " | "
        << shared::fillSpace(error, 15) << " |" << std::endl;
}

int largest(const int& a, const int& b, const int& c) {
    if (a >= b) {
        if (a >= c) return a;
        return c;
    }
    if (b >= c) return b;
    return c;
}

void task1() {
    std::cout << "Task 1" << std::endl;

    double x = shared::numFromConsole("Enter starting X (minimal): ");
    const double xEnd = shared::numFromConsole("Enter ending X (maximum): ");
    if (x >= xEnd) {
        std::cout << "Starting X can't be larger or equal to ending X" << std::endl;
        return;
    }
    const double xStep = shared::numFromConsole("Enter step of X: ");
    const double accuracy = shared::numFromConsole(
      "Enter accuracy of counting exponential Taylor expansion (from 10^-2 to 10^-6): "
    );

    const int xPrecision = largest(
       calculatePrecision(xStep),
       calculatePrecision(x),
       calculatePrecision(xEnd)
    );

    std::cout
        << "|-----------------|-----------------|-----------------|-----------------|"
        << std::endl
        << "| x               | y               | standard        | error           |"
        << std::endl
        << "|-----------------|-----------------|-----------------|-----------------|"
        << std::endl;

    while (x <= xEnd) {
        if (x < -2 || x > 1) {
            showNoSolution(x);
        }
        else if (x < 0) {
            const double arctg = atan(x);
            const double y = exponentialTaylorExpansion(arctg, accuracy);
            const double standard = exp(arctg);
            showState(x, y, standard, fabs(standard - y));
        }
        else {
            const double xSquare = x * x;
            const double y = exponentialTaylorExpansion(xSquare, accuracy) + 1;
            const double standard = exp(xSquare) + 1;
            showState(x, y, standard, fabs(standard - y));
        }

        // required to keep calculations in right state
        // IDEA: move all calculations to custom fraction struct or strings
        x = roundToPrecision(x + xStep, xPrecision);
    }

    std::cout << shared::LINE_SEPARATOR << std::endl;
}

/// <summary>
/// Calculates factorial of number. If factorial is too large
/// to put into unsigned long long, then it will return nullopt.
/// </summary>
std::optional<unsigned long long> factorial(const long& number) noexcept {
    unsigned long long result = 1;
    for (long i = 2; i <= number; i += 1) {
        // Check for overflow of result
        if (result > ULLONG_MAX / i) return std::nullopt;
        result *= i;
    }
    return result;
}

/// <summary>
/// Calculate binomial power with standard functions and recalculations each time.
/// Used to check correctness of newtonBinomialPower.
/// </summary>
std::optional<long double> slowBinomialPower(
  const double& a, const double& b, const long& n
) {
    long double result = 0;
    for (long k = 0; k <= n; k += 1) {
        const auto nFactorial = factorial(n);
        if (!nFactorial.has_value()) return std::nullopt;

        const auto kFactorial = factorial(k);
        if (!kFactorial.has_value()) return std::nullopt;

        const auto nMinusKFactorial = factorial(n - k);
        if (!nMinusKFactorial.has_value()) return std::nullopt;

        const long double binomialCoefficient = (
          nFactorial.value() * 1.0 / (kFactorial.value() * nMinusKFactorial.value())
        );
        result += binomialCoefficient * pow(a, k) * pow(b, n - k);
    }
    return result;
}

/// <summary>
/// Calculate binomial power with Newton formula with recurrence relations.
/// </summary>
std::optional<long double> newtonBinomialPower(
  const double& a, const double& b, const long& n
) {
    // should get it anyway at the start
    const auto nFactorial = factorial(n);
    if (!nFactorial.has_value()) return std::nullopt;
    long double result = 0;

    unsigned long long kFactorial = 1;
    long double aPow = 1;
    long double bPow = pow(b, n);
    unsigned long long nMinusKFactorial = nFactorial.value();

    for (long k = 0; k <= n;) {
        const long  double binomialCoefficient = (
          nFactorial.value() * 1.0 / (kFactorial * nMinusKFactorial)
        );
        result += binomialCoefficient * aPow * bPow;

        k += 1;
        kFactorial *= k;
        aPow *= a;
        bPow = bPow / b;

        const unsigned long long newNMinusKFactorial = nMinusKFactorial * 1.0 / (n - k + 1.0);
        nMinusKFactorial = newNMinusKFactorial < 1 ? 1 : newNMinusKFactorial;
    }

    return result;
}

void task2() {
    std::cout << "Task 2" << std::endl;

    const double a = shared::numFromConsole("Enter number A: ");
    const double b = shared::numFromConsole("Enter number B: ");
    const long n = lround(shared::numFromConsole("Enter natural power N (>0): "));
    if (n <= 0) {
        std::cout << "N can only be a natural number" << std::endl;
        return;
    }

    const auto slowResult = slowBinomialPower(a, b, n);
    if (!slowResult.has_value() || isnan(slowResult.value()) || isinf(slowResult.value())) {
        std::cout << "Number is too big to calculate." << std::endl;
        std::cout << shared::LINE_SEPARATOR << std::endl;
        return;
    }

    std::cout << "Slow Result to check correctness: " << slowResult.value() << std::endl;

    const auto result = newtonBinomialPower(a, b, n);
    if (!result.has_value() || isnan(result.value()) || isinf(result.value())) {
        std::cout << "Number is too big to calculate." << std::endl;
        std::cout << shared::LINE_SEPARATOR << std::endl;
        return;
    }

    std::cout << "Result: " << result.value() << std::endl;

    std::cout
        << "Results are equal: "
        << (slowResult.value() == result.value() ? "Yes" : "No")
        << std::endl;

    std::cout << shared::LINE_SEPARATOR << std::endl;
}

void run() {
    std::cout << "Lab 4" << std::endl;

    shared::select({ {"Task 1", task1}, {"Task 2", task2} });
}
}