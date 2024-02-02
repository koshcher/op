#pragma once

struct ArrayItem {
    int number;
    int index;
};

// { 0, -1 } if not found positive
ArrayItem minPositiveInArray(const int* arr, const int& length) {
    ArrayItem result = { 0, -1 };

    for (int i = 0; i < length; i += 1) {
        const int& current = arr[i];
        if (current <= 0) continue;

        if (result.number <= 0 || current < result.number) {
            result.number = current;
            result.index = i;
        }
    }

    return result;
}

void insert(const int*& arr, int& length, int value, int index) {
    if (index < 0 || index > length) return;

    int* newArr = new int[length + 1];
    for (int i = 0; i < index; i += 1) {
        newArr[i] = arr[i];
    }
    newArr[index] = value;
    for (int i = index; i < length; i += 1) {
        newArr[i + 1] = arr[i];
    }

    delete[] arr;
    arr = newArr;
    length += 1;
}