#pragma once

#include <memory>
#include <iostream>

namespace str {
struct Str {
    // array of symbols
    std::unique_ptr<char[]> data;

    // count of allocated memory for all chars including \0
    int capacity;
};

// allocate new memory for str and fill with \0
Str makeStr(const int& capacity) {
    Str str = Str { std::make_unique<char[]>(capacity), capacity };
    for (int i = 0; i < capacity; i += 1) {
        str.data[i] = '\0';
    }
    return str;
}

// allocate more memory for str
void expand(Str& str, const int& additionalCapacity) {
    Str newStr = makeStr(str.capacity + additionalCapacity);
    for (int i = 0; i < str.capacity; i += 1) {
        newStr.data[i] = str.data[i];
    }
    str = std::move(newStr);
}

void print(const Str& str) {
    for (int i = 0; i < str.capacity; i += 1) {
        const auto& symbol = str.data[i];
        if (symbol == '\0') break;
        std::cout << symbol;
    }
}

// reducing capacity to minimal possible, remove unused memory
void compress(Str& str) {
    if (str.capacity <= 1) return;

    int newCapacity = 1;
    for (int i = 0; i < str.capacity; i += 1) {
        if (str.data[i] == '\0') break;
        newCapacity += 1;
    }
    if (newCapacity == str.capacity) return;

    Str compressedStr = makeStr(newCapacity);
    for (int i = 0; i < newCapacity; i += 1) {
        compressedStr.data[i] = str.data[i];
    }
    str = std::move(compressedStr);
}

// get str from console
Str enterStr(int bufferSize = 256) {
    Str str = makeStr(bufferSize);

    char symbol;
    int index = 0;

    while (std::cin.get(symbol) && symbol != '\n') {
        // last symbol mast remaint \0
        if (index >= str.capacity - 1) {
            expand(str, bufferSize);
        }

        str.data[index] = symbol;
        index += 1;
    }
    compress(str);
    return str;
}

// returns -1 if symbol isn't found in str
int indexOf(const Str& str, const char& symbol) {
    for (int i = 0; i < str.capacity; i += 1) {
        const auto& c = str.data[i];
        if (c == symbol) return i;
        if (c == '\0') break;
    }
    return -1;
}

Str copy(const Str& str) {
    Str newStr = makeStr(str.capacity);
    for (int i = 0; i < str.capacity; i += 1) {
        newStr.data[i] = str.data[i];
    }
    return newStr;
}

int symbolsCount(const Str& str) {
    for (int i = 0; i < str.capacity; i += 1) {
        if (str.data[i] == '\0') return i;
    }
    return 0;
}

bool areEqual(const Str& str1, const Str& str2) {
    if (str1.capacity != str2.capacity) return false;

    for (int i = 0; i < str1.capacity; i += 1) {
        if (str1.data[i] != str2.data[i]) return false;
    }
    return true;
}
}

void test() {
    str::Str me = str::enterStr();
    str::Str dad = str::enterStr();

    bool equal = str::areEqual(me, dad);
    int a = str::indexOf(me, 'a');

    auto meCopy = str::copy(me);
    str::print(meCopy);

    meCopy.data[0] = 'Q';
    str::print(meCopy);
}