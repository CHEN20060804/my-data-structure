//
// Created by yyc08 on 25-7-12.
//

#ifndef MY_DATA_STRUCTURE_STACK_H
#define MY_DATA_STRUCTURE_STACK_H

#include <stdexcept>

namespace yc {
    template<typename T>
    class Stack {
    private:
        T* data;
        int size;
        int capacity;
        void resize();
    public:
        Stack();
        ~Stack();
        void push(const T& value);
        T pop();
        T top() const;
        int getSize() const;
    };

    template<typename T>
    Stack<T>::Stack() : size(0), capacity(10) {
        data = new T[capacity];
    }

    template<typename T>
    Stack<T>::~Stack() {
        delete[] data;
    }

    template<typename T>
    void Stack<T>::resize() {
        capacity *= 2;
        T* newData = new T[capacity];
        for (int i = 0; i < size; ++i) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
    }

    template<typename T>
    void Stack<T>::push(const T &value) {
        if(size == capacity) {
            resize();
        }
        data[size++] = value;
    }

    template<typename T>
    T Stack<T>::pop() {
        if(size == 0) {
            throw std::out_of_range("Stack is empty");
        }
        return data[--size];
    }

    template<typename T>
    T Stack<T>::top() const {
        if(size == 0) {
            throw std::out_of_range("Stack is empty");
        }
        return data[size - 1];
    }

    template <typename T>
    int Stack<T>::getSize() const {
        return size;
    }

} // yc

#endif //MY_DATA_STRUCTURE_STACK_H
