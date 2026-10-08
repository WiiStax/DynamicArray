#include "DynamicArray.h"
#include <iostream>
#include <limits>

int readInt(const char* prompt) {
    int value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value) {
            return value;
        }
        std::cout << "Must be integer\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

std::size_t readSize(const char* prompt) {
    while (true) {
        const int value = readInt(prompt);
        if (value >= 0) {
            return static_cast<std::size_t>(value);
        }
        std::cout << "Size can't be negative\n";
    }
}

void fillArray(DynamicArray& array, const char* name) {
    std::cout << "Input " << array.size() << " array element(s) " << name << " (from -100 to 100):\n";
    for (std::size_t i = 0; i < array.size(); ++i) {
        while (true) {
            std::cout << name << '[' << i << "] = ";
            const int value = readInt("");
            if (array.set(i, value)) {
                break;
            }
            std::cout << "Elements must be from -100 to 100\n";
        }
    }
}

int main() {
    DynamicArray a(readSize("Input array size: "));
    fillArray(a, "ArrayTest");

    std::cout << "ArrayTest = ";
    a.print();

    if (a.size() > 0) {
        const std::size_t index = readSize("Input index to read from ArrayTest: ");
        int value = 0;
        if (a.get(index, value)) {
            std::cout << "A[" << index << "] = " << value << '\n';
        } else {
            std::cout << "Index out of bounds\n";
        }

        const std::size_t setIndex = readSize("Enter index to change an element: ");
        const int newValue = readInt("Input new element (-100..100): ");
        if (a.set(setIndex, newValue)) {
            std::cout << "New ArrayTest = ";
            a.print();
        } else {
            std::cout << "Invalid input for setter\n";
        }
    } else {
        std::cout << "ArrayTest is empty, can't change it\n";
    }

    DynamicArray copy(a);
    std::cout << "Copy of ArrayTest = ";
    copy.print();

    const int appendedValue = readInt("Enter an element to add (-100..100): ");
    if (a.append(appendedValue)) {
        std::cout << "ArrayTest after adding = ";
        a.print();
        std::cout << "New ArrayTest size " << a.size() << '\n';
    } else {
        std::cout << "Invalid element, can't add\n";
    }

    DynamicArray b(readSize("Enter ArrayTest2 size: "));
    fillArray(b, "");
    std::cout << "ArrayTest2 = ";
    b.print();

    DynamicArray sum(a);
    sum.add(b);
    std::cout << "ArrayTest + ArrayTest2 (result put in ArrayTest copy) = ";
    sum.print();

    DynamicArray difference(a);
    difference.subtract(b);
    std::cout << "ArrayTest - ArrayTest2 (result put in ArrayTest copy) = ";
    difference.print();
    
    return 0;
}
