#include "DynamicArray.h"
#include <iostream>
#include <limits>
#include <new>
#include <stdexcept>

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
            try {
                array.set(i, value);
                break;
            } catch (const std::invalid_argument& e) {
                std::cout << "Value Error: " << e.what() << '\n';
            }
        }
    }
}

void demonstrateOutOfRange(DynamicArray& array) {
    std::cout << "\nChecking std::out_of_range:\n";
    const std::size_t index = readSize("Enter index to read from ArrayTest: ");
    try {
        std::cout << "ArrayTest[" << index << "] = " << array.get(index) << '\n';
    } catch (const std::out_of_range& e) {
        std::cout << "Caught std::out_of_range: " << e.what() << '\n';
    }
}

void demonstrateInvalidArgument(DynamicArray& array) {
    std::cout << "\nChecking std::invalid_argument:\n";
    const int value = readInt("Enter value for ArrayTest[0]: ");
    try {
        array.set(0, value);
        std::cout << "Value read successfully.\n";
    } catch (const std::invalid_argument& e) {
        std::cout << "Caught std::invalid_argument: " << e.what() << '\n';
    } catch (const std::out_of_range& e) {
        std::cout << "Caught std::out_of_range: " << e.what() << '\n';
    }
}

void demonstrateBadAlloc() {
    std::cout << "\nChecking std::bad_alloc:\n";
    try {
        std::size_t size = readSize("Enter ArrayTest size: ");
        DynamicArray test(size);
        std::cout << "Array created, size: " << test.size() << '\n';
    }
    catch (const std::bad_alloc& e) {
        std::cout << "Memory allocation error: " << e.what() << '\n';
    }
}

int main() {
    try {
        DynamicArray a(readSize("Input array A size: "));
        fillArray(a, "A");
        std::cout << "A = ";
        a.print();

        if (a.size() > 0) {
            demonstrateOutOfRange(a);
            demonstrateInvalidArgument(a);

            const int value = readInt("Input an element to add (-100..100): ");
            try {
                a.append(value);
                std::cout << "New A = ";
                a.print();
            } catch (const std::invalid_argument& e) {
                std::cout << "Caught std::invalid_argument: " << e.what() << '\n';
            } catch (const std::bad_alloc& e) {
                std::cout << "Caught std::bad_alloc: " << e.what() << '\n';
            }
        } else {
            std::cout << "A is empty.\n";
        }

        DynamicArray copy(a);
        std::cout << "Copy of A = ";
        copy.print();

        DynamicArray b(readSize("Enter array B size: "));
        fillArray(b, "B");
        std::cout << "B = ";
        b.print();

        DynamicArray sum(a);
        sum.add(b);
        std::cout << "A + B = ";
        sum.print();

        DynamicArray difference(a);
        difference.subtract(b);
        std::cout << "A - B = ";
        difference.print();

        demonstrateBadAlloc();
    } catch (const std::bad_alloc& e) {
        std::cerr << "Memory allocation error (std::bad_alloc): " << e.what() << '\n';
        return 1;
    } catch (const std::exception& e) {
        std::cerr << "Unexpected exception: " << e.what() << '\n';
        return 1;
    }

    return 0;
}