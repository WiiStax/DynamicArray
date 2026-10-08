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

    bool set(std::size_t index, int value) noexcept;

    bool get(std::size_t index, int& outValue) const noexcept;

    void print() const;

    bool append(int value);

    void add(const DynamicArray& other) noexcept;

    void subtract(const DynamicArray& other) noexcept;
};

#endif