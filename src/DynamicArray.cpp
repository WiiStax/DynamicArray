#include "DynamicArray.h"
#include <iostream>
#include <stdexcept>

DynamicArray::DynamicArray(std::size_t size)
    : data_(size == 0 ? nullptr : new int[size]{}), size_(size) {}

DynamicArray::DynamicArray(const DynamicArray& other)
    : data_(other.size_ == 0 ? nullptr : new int[other.size_]), size_(other.size_) {
    for (std::size_t i = 0; i < size_; ++i) {
        data_[i] = other.data_[i];
    }
}

DynamicArray::~DynamicArray() {
    delete[] data_;
}

std::size_t DynamicArray::size() const noexcept {
    return size_;
}

void DynamicArray::set(std::size_t index, int value) {
    if (index >= size_) {
        throw std::out_of_range("DynamicArray::set: index is outside the array");
    }
    if (value < -100 || value > 100) {
        throw std::invalid_argument("DynamicArray::set: value must be in [-100, 100]");
    }

    data_[index] = value;
}

int DynamicArray::get(std::size_t index) const {
    if (index >= size_) {
        throw std::out_of_range("DynamicArray::get: index is outside the array");
    }
    return data_[index];
}

void DynamicArray::print() const {
    std::cout << "{";
    for (std::size_t i = 0; i < size_; ++i) {
        if (i > 0) {
            std::cout << ", ";
        }
        std::cout << data_[i];
    }
    std::cout << "}\n";
}

void DynamicArray::append(int value) {
    if (value < -100 || value > 100) {
        throw std::invalid_argument("DynamicArray::append: value must be in [-100, 100]");
    }

    int* newData = new int[size_ + 1];
    for (std::size_t i = 0; i < size_; ++i) {
        newData[i] = data_[i];
    }
    newData[size_] = value;

    delete[] data_;
    data_ = newData;
    ++size_;
}

void DynamicArray::add(const DynamicArray& other) noexcept {
    const std::size_t commonSize = size_ < other.size_ ? size_ : other.size_;
    for (std::size_t i = 0; i < commonSize; ++i) {
        int result = data_[i] + other.data_[i];
        data_[i] = result;
    }
}

void DynamicArray::subtract(const DynamicArray& other) noexcept {
    const std::size_t commonSize = size_ < other.size_ ? size_ : other.size_;
    for (std::size_t i = 0; i < commonSize; ++i) {
        int result = data_[i] - other.data_[i];
        data_[i] = result;
    }
}
