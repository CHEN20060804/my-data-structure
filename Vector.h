//
// Created by yyc08 on 25-7-23.
//

#ifndef VECTOR_H
#define VECTOR_H
#include <stdexcept>

namespace yc {

    template<typename T>
    class Vector {
    private:
        T* data;
        size_t size;
        size_t capacity;

        void resize() {
            if (capacity == 0) {
                capacity = 1;
            }
            capacity *= 2;
            T* newData = new T[capacity];
            for (size_t i = 0; i < size; i++) {
                newData[i] = data[i];
            }
            delete[] data;
            data = newData;
        }
    public:
        Vector() : data(new T[10]), size(0), capacity(10) {}

        explicit Vector(const size_t& initialSize) : data(new T[initialSize]), size(0), capacity(initialSize) {
            if (initialSize == 0) {
                throw std::invalid_argument("Initial size must be greater than 0");
            }
        }

        Vector(const size_t& initialSize, const T& value) : data(new T[initialSize * 2]), size(initialSize), capacity(initialSize * 2) {
            if (initialSize == 0) {
                throw std::invalid_argument("Initial size must be greater than 0");
            }
            for (size_t i = 0; i < initialSize; i++) {
                data[i] = value;
            }
        }

        ~Vector() {
            delete[] data;
        }

        Vector(const Vector& other) : data(new T[other.capacity]), size(other.size), capacity(other.capacity) {
            for (size_t i = 0; i < size; i++) {
                data[i] = other.data[i];
            }
        }

        Vector& operator=(const Vector& other) {
            if (this != &other) {
                delete[] data;
                data = new T[other.capacity];
                size = other.size;
                for (size_t i = 0; i < size; i++) {
                    data[i] = other.data[i];
                }
            }
            return *this;
        }

        Vector(Vector&& other) noexcept : data(other.data), size(other.size), capacity(other.capacity) {
            other.data = nullptr;
            other.size = 0;
            other.capacity = 0;
        }

        Vector& operator=(Vector&& other) noexcept {
            if (this != &other) {
                delete[] data;
                data = other.data;
                size = other.size;
                capacity = other.capacity;
                other.data = nullptr;
                other.size = 0;
                other.capacity = 0;
            }
            return *this;
        }

        size_t getSize() const {
            return size;
        }

        size_t getCapacity() const {
            return capacity;
        }

        T* getData() {
            return data;
        }

        T& operator[](const size_t& index) {
            if (index >= size) {
                throw std::out_of_range("Index out of bounds");
            }
            return data[index];
        }

        const T& operator[](const size_t& index) const {
            if (index >= size) {
                throw std::out_of_range("Index out of bounds");
            }
            return data[index];
        }

        void push_back(const T& value) {
            if (size >= capacity) {
                resize();
            }
            data[size++] = value;
        }

        void push_back(T&& value) {
            if (size >= capacity) {
                resize();
            }
            data[size++] = std::move(value);
        }

        void pop_back() {
            if (size == 0) {
                throw std::out_of_range("Vector is empty");
            }
            --size;
        }

        T* begin() {
            return data;
        }

        T* end() {
            return data + size;
        }

        const T* begin() const {
            return data;
        }

        const T* end() const {
            return data + size;
        }

    };

} // yc

#endif //VECTOR_H
