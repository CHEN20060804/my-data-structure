//
// Created by yyc08 on 25-7-18.
//

#ifndef MY_DATA_STRUCTURE_QUEUE_H
#define MY_DATA_STRUCTURE_QUEUE_H
#include <stdexcept>
namespace yc {
    template<typename T>
    class Queue {
    private:
        T* data;
        int front;
        int rear;
        int capacity;
        void resize();

    public:
        Queue();
        ~Queue();
        Queue(const Queue<T>& other) = delete; // Disable copy constructor
        void operator=(const Queue<T>& other) = delete; // Disable copy assignment
        void enqueue(const T& value);
        T dequeue();
        T getFront() const;
        int getSize() const;
    };

    template<typename T>
    void Queue<T>::resize() {
        int oldCap = capacity;
        capacity *= 2;
        T* newData = new T[capacity];
        int size = getSize();
        for (int i = 0; i < size; ++i) {
            newData[i] = data[(front + i) % oldCap];
        }
        delete[] data;
        data = newData;
        front = 0;
        rear = size;
    }

    template<typename T>
    Queue<T>::Queue() : front(0), rear(0), capacity(10) {
        data = new T[capacity];
    }
    template<typename T>
    Queue<T>::~Queue() {
        delete[] data;
    }

    template<typename T>
    void Queue<T>::enqueue(const T& value) {
        if((rear + 1) % capacity == front) {
            resize();
        }
        data[rear] = value;
        rear = (rear + 1) % capacity;
    }

    template<typename T>
    T Queue<T>::dequeue() {
        if(front == rear) {
            throw std::out_of_range("Queue is empty");
        }
        T val = data[front];
        front = (front + 1) % capacity;
        return val;
    }

    template<typename T>
    T Queue<T>::getFront() const {
        if(front == rear) {
            throw std::out_of_range("Queue is empty");
        }
        return data[front];
    }

    template<typename T>
    int Queue<T>::getSize() const {
        return (rear - front + capacity) % capacity;
    }
}
#endif //MY_DATA_STRUCTURE_QUEUE_H
