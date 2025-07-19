//
// Created by yyc08 on 25-7-19.
//

#ifndef MY_DATA_STRUCTURE_STRING_H
#define MY_DATA_STRUCTURE_STRING_H

#include <cstring>
#include <iostream>
#include <stdexcept>

namespace yc {

    class String {
    private:
        char* str;
        size_t length;

    public:

        String() : str(new char[1]{'\0'}), length(0) {}

        explicit String(const char* s) : length(s ? strlen(s) : 0) {
            if (!s) {
                str = new char[1]{'\0'};
            } else {
                str = new char[length + 1];
                strcpy(str, s);
            }
        }

        String(const String& other) : length(other.length) {
            str = new char[length + 1];
            strcpy(str, other.str);
        }

        ~String() {
            delete[] str;
            str = nullptr;
        }

        size_t len() const {
            return length;
        }

        char& operator[](size_t index) {
            if(index >= length) {
                throw std::out_of_range("Index out of bounds");
            }
            return str[index];
        }

        const char& operator[](size_t index) const {
            if(index >= length) {
                throw std::out_of_range("Index out of bounds");
            }
            return str[index];
        }

        String& operator=(const String& other) {
            if(this != &other) {
                delete[] str;
                length = other.length;
                str = new char[length + 1];
                strcpy(str, other.str);
            }
            return *this;
        }

        bool operator==(const String& other) const {
            return strcmp(str, other.str) == 0;
        }

        bool operator!=(const String& other) const {
            return !(*this == other);
        }

        String operator+(const String& other) const {
            size_t newLength = other.length + length;
            char* newStr = new char[newLength + 1];
            strcpy(newStr, str);
            strcat(newStr, other.str);
            String result(newStr);
            delete[] newStr;
            return result;
        }

        friend std::ostream& operator<<(std::ostream& os, const String& s) {
            os << s.str;
            return os;
        }
    };

} // yc

#endif //MY_DATA_STRUCTURE_STRING_H
