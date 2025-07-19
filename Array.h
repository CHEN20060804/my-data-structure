//
// Created by yyc08 on 25-7-19.
//

#ifndef MY_DATA_STRUCTURE_ARRAY_H
#define MY_DATA_STRUCTURE_ARRAY_H
#include <cstddef>
#include <stdexcept>
namespace yc {
    template<typename T, size_t N>
    class Array {
    private:
        T data[N];
    public:
        Array() {
            for (size_t i = 0; i < N; ++i) {
                data[i] = T{};  // 以 T 的默认值初始化每个元素
            }
        }
        Array(const Array&) = default;
        Array(Array&&) = default;
        Array& operator=(const Array&) = default;
        Array& operator=(Array&&) = default;
        ~Array() = default;

        constexpr size_t size() const {
            return N;
        }


        T& operator[](size_t index) {
            if(index >= N) {
                throw std::out_of_range("Index out of bounds");
            }
            return data[index];
        }
         T& operator[](size_t index) const {
            if(index >= N) {
                throw std::out_of_range("Index out of bounds");
            }
            return data[index];
        }

        T* begin() {
            return data;
        }
        T* end() {
            return data + N;
        }
        const T* begin() const {
            return data;
        }
        const T* end() const {
            return data + N;
        }

    };
}

#endif //MY_DATA_STRUCTURE_ARRAY_H
