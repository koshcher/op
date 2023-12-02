#pragma once

#include "shared.h"

namespace lab9 {
// LIB

struct Str {
    std::unique_ptr<char[]> data;
    int length;
};

Str makeStr(const int& length) {
    Str str = Str { std::make_unique<char[]>(length), length };
    for (int i = 0; i < length; i += 1) {
        str.data[i] = '\0';
    }
    return str;
}

void expandStr(Str& str, const int& additionalLength) {
    Str newStr = makeStr(str.length + additionalLength);
    for (int i = 0; i < str.length; i += 1) {
        newStr.data[i] = str.data[i];
    }
    str = std::move(newStr);
}

// remove unused memory
void compressStr(Str& str) {
    if (str.length <= 1) return;

    int newLength = 1;
    for (int i = 0; i < str.length; i += 1) {
        if (str.data[i] == '\0') break;
        newLength += 1;
    }
    if (newLength == str.length) return;

    Str compressedStr = makeStr(newLength);
    for (int i = 0; i < newLength; i += 1) {
        compressedStr.data[i] = str.data[i];
    }
    str = std::move(compressedStr);
}

// -1 if char isn't found
int symbolIndex(const Str& str, const char& symbol) {
    for (int i = 0; i < str.length; i += 1) {
        const auto& c = str.data[i];
        if (c == '\0') break;
        if (c == symbol) return i;
    }
    return -1;
}

void printlnStr(const Str& str) {
    for (int i = 0; i < str.length; ++i) {
        const auto& symbol = str.data[i];
        if (symbol == '\0') break;
        std::cout << symbol;
    }
    std::cout << std::endl;
}

void printStr(const Str& str) {
    for (int i = 0; i < str.length; ++i) {
        const auto& symbol = str.data[i];
        if (symbol == '\0') break;
        std::cout << symbol;
    }
}

const int BUFFER_SIZE = 256;

Str enterString() {
    Str str = makeStr(BUFFER_SIZE);

    char symbol;
    int index = 0;

    while (std::cin.get(symbol) && symbol != '\n') {
        // last symbol mast remaint \0
        if (index >= str.length - 1) {
            expandStr(str, BUFFER_SIZE);
        }

        str.data[index] = symbol;
        index += 1;
    }
    compressStr(str);
    return str;
}

Str copyStr(const Str& str) {
    Str newStr = makeStr(str.length);
    for (int i = 0; i < str.length; i += 1) {
        newStr.data[i] = str.data[i];
    }
    return newStr;
}

bool areStrEquar(const Str& str1, const Str& str2) {
    if (str1.length != str2.length) return false;

    for (int i = 0; i < str1.length; i += 1) {
        if (str1.data[i] != str2.data[i]) return false;
    }
    return true;
}

struct Streak {
    char symbol;
    int count;
};

void printStreak(const Streak& streak) {
    for (int i = 0; i < streak.count; i += 1) {
        std::cout << streak.symbol;
    }
    std::cout << std::endl;
}

struct StrArray {
    std::unique_ptr<Str[]> data;
    int size;
};

StrArray makeStrArray(const int& size) {
    return StrArray { std::make_unique<Str[]>(size), size };
}

void expandStrArray(StrArray& arr) {
    StrArray newArr = makeStrArray(arr.size + 1);
    for (int i = 0; i < arr.size; i += 1) {
        newArr.data[i] = std::move(arr.data[i]);
    }
    arr = std::move(newArr);
}

void printStrArray(const StrArray& arr) {
    for (int i = 0; i < arr.size; i += 1) {
        std::cout << '\'';
        const auto& str = arr.data[i];
        for (int j = 0; j < str.length; j += 1) {
            std::cout << str.data[j];
        }
        std::cout << '\'' << std::endl;
    }
}

// TASKS

bool isSymmetricRelativeToIndex(const Str& str, const int& index) {
    if (index < 0 || index >= str.length - 1) return false;
    if (str.length <= 3) return false;

    int leftIndex = index - 1;
    int rightIndex = index + 1;

    while (leftIndex >= 0 && rightIndex < str.length - 1) {
        if (str.data[leftIndex] != str.data[rightIndex]) {
            return false;
        }

        leftIndex -= 1;
        rightIndex += 1;
    }
    return true;
}

bool isSeparator(const char& symbol) {
    if (symbol == ' ') return true;
    if (symbol == '.') return true;
    if (symbol == ',') return true;
    if (symbol == '!') return true;
    if (symbol == '?') return true;
    return false;
}

std::optional<Streak> longestIdenticalSymbolsStreak(const Str& str) {
    if (str.length <= 0) return std::nullopt;

    char currentChar = str.data[0];
    int currentLength = 1;

    char longestChar = currentChar;
    int longestLength = 1;

    for (int i = 1; i < str.length; i += 1) {
        const auto& c = str.data[i];
        if (isSeparator(c)) continue;

        if (c == currentChar) {
            currentLength += 1;
        }
        else {
            currentChar = c;
            currentLength = 1;
        }

        if (currentLength > longestLength) {
            longestChar = currentChar;
            longestLength = currentLength;
        }
    }

    return Streak { longestChar, longestLength };
}

void removeSame(Str& str) {
    if (str.length <= 1) return;

    int newLength = 1;
    for (int i = 1; i < str.length; i += 1) {
        if (str.data[i] != str.data[i - 1]) {
            newLength += 1;
        }
    }

    std::unique_ptr<char[]> newData = std::make_unique<char[]>(newLength + 1);
    newData[newLength] = '\0';

    int newIndex = 0;
    newData[newIndex++] = str.data[0];
    for (int i = 1; i < str.length; ++i) {
        if (str.data[i] != str.data[i - 1]) {
            newData[newIndex++] = str.data[i];
        }
    }

    str.data = std::move(newData);
    str.length = newLength + 1;
}

void task1() {
    std::cout << "Enter string: " << std::endl;
    Str string = enterString();

    std::cout
        << "Select action:" << std::endl
        << "[0] longest sequence of the same characters in a row" << std::endl
        << "[1] check if string is symmetrical relative to position" << std::endl
        << "[2] check if string is symmetrical relative to symbol" << std::endl
        << "[3] remove same characters stack string" << std::endl;

    int action = shared::intFromConsole("");
    if (action < 0 || action > 3) {
        std::cout << "Option doesn't exist" << std::endl;
    }

    if (action == 0) {
        const auto streak = longestIdenticalSymbolsStreak(string);
        if (!streak.has_value()) {
            std::cout << "String is empty" << std::endl;
        }
        else {
            std::cout << "Longest streak: ";
            printStreak(streak.value());
        }
    }
    else if (action == 1) {
        std::cout
            << "Enter position (symbol number) from where to check if symmetric"
            << std::endl;
        int position = shared::intFromConsole("");

        const bool symmetric = isSymmetricRelativeToIndex(string, position - 1);
        if (symmetric) {
            std::cout << "String is symmetric" << std::endl;
        }
        else {
            std::cout << "String is NOT symmetric" << std::endl;
        }
    }
    else if (action == 2) {
        std::cout << "Enter symbol from which to check if symmetric" << std::endl;
        char symbol = shared::charFromConsole();

        const bool symmetric = isSymmetricRelativeToIndex(
            string, symbolIndex(string, symbol)
        );
        if (symmetric) {
            std::cout << "String is symmetric" << std::endl;
        }
        else {
            std::cout << "String is NOT symmetric" << std::endl;
        }
    }
    else if (action == 3) {
        removeSame(string);
        std::cout << "New string without same characters in a row:" << std::endl;
        printlnStr(string);
    }

    std::cout << shared::LINE_SEPARATOR << std::endl;
}

StrArray splitIntoWords(const Str& str) {
    StrArray words = makeStrArray(0);

    int wordStartIndex = 0;
    int wordEndIndex = -1;

    for (int i = 0; i < str.length; i += 1) {
        const auto& symbol = str.data[i];

        if (std::isalpha(symbol)) {
            wordEndIndex = i;
            continue;
        }

        if (wordEndIndex >= 0) {
            int wordLength = (wordEndIndex - wordStartIndex) + 2;
            Str word = makeStr(wordLength);
            for (int j = wordStartIndex; j <= wordEndIndex; j += 1) {
                word.data[j - wordStartIndex] = str.data[j];
            }
            expandStrArray(words);
            words.data[words.size - 1] = std::move(word);
            wordEndIndex = -1;
        }

        wordStartIndex = i + 1;
    }
    return words;
}

bool isAnagram(const Str& word1, const Str& word2) {
    if (word1.length != word2.length) return false;

    Str marker = copyStr(word2);

    for (int i = 0; i < word1.length - 1; i += 1) {
        const auto& symbol = word1.data[i];
        const int index = symbolIndex(marker, symbol);

        if (index < 0) return false;
        marker.data[index] = '.';
    }
    return true;
}

void showAnagrams(const StrArray& words, const StrArray& dict) {
    for (int i = 0; i < words.size; i += 1) {
        const auto& strWord = words.data[i];
        bool hasAnagram = false;

        for (int j = 0; j < dict.size; j += 1) {
            const auto& dictWord = dict.data[j];

            if (
                !isAnagram(strWord, dictWord)
                || areStrEquar(strWord, dictWord)
            ) continue;

            if (!hasAnagram) {
                printStr(strWord);
                hasAnagram = true;
            }

            std::cout << " - ";
            printStr(dictWord);
        }

        if (hasAnagram) {
            std::cout << std::endl;
        }
    }
}

/*
    Test string:
    Moms listen to dads, earth altering heart

    Dictionary:
    silent
    enlist
    heart
    earth
    hater
    integral
    triangle
    alerting
*/
void task2() {
    std::cout << "Enter string to process:" << std::endl;

    Str string = enterString();

    int dictCount = shared::positiveIntFromConsole("Enter count of words in dictionary: ");
    std::cout << "Enter words of dictionary" << std::endl;
    StrArray dict = makeStrArray(dictCount);
    for (int i = 0; i < dictCount; i += 1) {
        dict.data[i] = enterString();
    }

    std::cout << shared::LINE_SEPARATOR << std::endl;

    StrArray words = splitIntoWords(string);
    std::cout << "Words of your string:" << std::endl;
    printStrArray(words);

    std::cout << shared::LINE_SEPARATOR << std::endl;

    std::cout << "Anagrams:" << std::endl;
    showAnagrams(words, dict);

    std::cout << shared::LINE_SEPARATOR << std::endl;
}

void run() {
    std::cout << "Lab 9" << std::endl;

    shared::select({ { "Task 1", task1 }, { "Task 2", task2 } });

    std::cout << shared::LINE_SEPARATOR << std::endl;
}
}