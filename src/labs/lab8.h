#pragma once

#include "shared.h"

namespace lab8 {
// STRUCTURES

struct NumArray {
    int* data;
    int count;
};

NumArray makeNumArray(const int& count) {
    return NumArray { new int[count], count };
}

NumArray copNumArray(const NumArray& arr) {
    NumArray newArr = makeNumArray(arr.count);
    for (int i = 0; i < arr.count; ++i) {
        newArr.data[i] = arr.data[i];
    }
    return newArr;
}

void pushToHistory(NumArray*& history, int& count, const NumArray& snapshot) {
    if (history == nullptr) {
        history = new NumArray[1];
        history[0] = snapshot;
        count = 1;
        return;
    }

    NumArray* newHistory = new NumArray[count + 1];
    for (int i = 0; i < count; ++i) {
        newHistory[i] = history[i];
    }
    newHistory[count] = snapshot;

    delete[] history;
    history = newHistory;
    count += 1;
}

NumArray currentArray(const NumArray* const& history, const int& count) {
    return history[count - 1];
}

// MUTATIONS

NumArray triangularNumArray() {
    int count = shared::intFromConsole("Enter count of triangular numbers: ");
    while (count <= 0) {
        count = shared::intFromConsole("Count must be more than 0. Enter count: ");
    }

    NumArray arr = makeNumArray(count);
    arr.data[0] = 1;
    for (int i = 1; i < arr.count; ++i) {
        arr.data[i] = arr.data[i - 1] + i + 1;
    }
    return arr;
}

NumArray multiplesOf5(const int* arr, const int& count) {
    int count5 = 0;
    for (int i = 0; i < count; ++i) {
        if (arr[i] % 5 == 0) {
            count5 += 1;
        }
    }

    NumArray multiples = makeNumArray(count5);
    int multiplesI = 0;

    for (int i = 0; i < count; ++i) {
        const int& num = arr[i];
        if (num % 5 == 0) {
            multiples.data[multiplesI] = num;
            multiplesI += 1;
        }
    }
    return multiples;
}

void deleteMultiplesOf3(int*& arr, int& count) {
    int notMultipleCount = 0;
    for (int i = 0; i < count; ++i) {
        if (arr[i] % 3 != 0) {
            notMultipleCount += 1;
        }
    }

    int* newArr = new int[notMultipleCount];
    int newArrI = 0;
    for (int i = 0; i < count; ++i) {
        const int& num = arr[i];
        if (num % 3 != 0) {
            newArr[newArrI] = num;
            newArrI += 1;
        }
    }

    delete[] arr;
    arr = newArr;
    count = notMultipleCount;
}

// INFO

void printNumArray(int const* const& data, const int& count) {
    for (int i = 0; i < count; ++i) {
        std::cout << data[i] << " ";
    }
    std::cout << std::endl;
}

void printHistory(const NumArray* history, const int& count) {
    for (int i = 0; i < count; ++i) {
        const NumArray& arr = history[i];
        for (int j = 0; j < arr.count; ++j) {
            std::cout << arr.data[j] << " ";
        }

        if (i != count - 1) {
            std::cout << std::endl << shared::LINE_SEPARATOR << std::endl;
        }
        else {
            std::cout << std::endl;
        }
    }
}

int countPerfectSquares(const int* arr, const int& count) {
    int squareCount = 0;

    for (int i = 1; i < count; ++i) {
        const int sum = arr[i] + arr[i - 1];

        for (int j = 1; j < sum / 2; ++j) {
            if (j * j == sum) {
                squareCount += 1;
            }
        }
    }
    return squareCount;
}

void run() {
    NumArray* history = nullptr;
    int historyCount = 0;

    std::cout << "Create array of triangular numbers to start" << std::endl;
    pushToHistory(history, historyCount, triangularNumArray());
    std::cout << shared::LINE_SEPARATOR << std::endl;

    int action = 0;
    while (action >= 0) {
        std::cout << "[0] - recreate array of triangular numbers" << std::endl;
        std::cout << "[1] - print current array" << std::endl;
        std::cout << "[2] - print history" << std::endl;
        std::cout << "[3] - count the number of complete squares of sums" << std::endl;
        std::cout << "[4] - create array of multiples of 5 from current" << std::endl;
        std::cout << "[5] - delete multiples of 3 from current array" << std::endl;
        std::cout << "[other] - finish" << std::endl;

        action = shared::intFromConsole("Enter action number: ");
        std::cout << shared::LINE_SEPARATOR << std::endl;

        if (action == 0) {
            pushToHistory(history, historyCount, triangularNumArray());
        }
        else if (action == 1) {
            const auto& arr = currentArray(history, historyCount);
            printNumArray(arr.data, arr.count);
        }
        else if (action == 2) {
            printHistory(history, historyCount);
        }
        else if (action == 3) {
            const auto& arr = currentArray(history, historyCount);
            const int count = countPerfectSquares(arr.data, arr.count);
            std::cout << "Count of perfect squares: " << count << std::endl;
        }
        else if (action == 4) {
            const auto& arr = currentArray(history, historyCount);
            const auto multiples = multiplesOf5(arr.data, arr.count);
            pushToHistory(history, historyCount, multiples);
            printNumArray(multiples.data, multiples.count);
        }
        else if (action == 5) {
            // need to create copy to keep history in a right shape
            NumArray arrCopy = copNumArray(currentArray(history, historyCount));
            deleteMultiplesOf3(arrCopy.data, arrCopy.count);
            pushToHistory(history, historyCount, arrCopy);
            printNumArray(arrCopy.data, arrCopy.count);
        }

        std::cout << shared::LINE_SEPARATOR << std::endl;
    }

    // free memory
    for (int i = 0; i < historyCount; ++i) {
        delete[] history[i].data;
    }
    delete[] history;
}
}