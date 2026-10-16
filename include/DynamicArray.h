#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <cstddef>

class DynamicArray {
private:
    int* data_;
    std::size_t size_;

public:
    explicit DynamicArray(std::size_t size = 0);
    DynamicArray(const DynamicArray& other);
    ~DynamicArray();

    std::size_t size() const noexcept;

    void set(std::size_t index, int value);

    int get(std::size_t index) const;

    void print() const;

    void append(int value);

    void add(const DynamicArray& other) noexcept;

    void subtract(const DynamicArray& other) noexcept;
};

#endif