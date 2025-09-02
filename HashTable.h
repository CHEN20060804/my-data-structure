//
// Created by yyc08 on 2025/9/1.
//

#ifndef MY_DATA_STRUCTURE_HASHTABLE_H
#define MY_DATA_STRUCTURE_HASHTABLE_H

#include <functional>

namespace yc {

    template<typename KeyType, typename ValueType>
    class HashTable {
    private:
        class HashNode {
        public:
            KeyType key;
            ValueType value;
            HashNode *next;
            HashNode(const KeyType &k, const ValueType &v) : key(k), value(v), next(nullptr) {}
        };

        HashNode** table;
        size_t size;

        size_t hash(const KeyType &k) const {
            return std::hash<KeyType>{}(k) % size;
        }

    public:
        explicit HashTable(size_t size = 128) : size(size) {
            if (size == 0) throw std::invalid_argument("HashTable size must be > 0");
            table = new HashNode*[size];
            for (size_t i = 0; i < size; ++i) {
                table[i] = nullptr;
            }
        }
        ~HashTable() {
            for (size_t i = 0; i < size; ++i) {
                HashNode* curr = table[i];
                while (curr != nullptr) {
                    HashNode* temp = curr->next;
                    delete curr;
                    curr = temp;
                }
                table[i] = nullptr;
            }
            delete[] table;
            table = nullptr;
        }
        HashTable(const HashTable &other) = delete; // 禁止拷贝构造
        HashTable(HashTable&& other) = delete; // 禁止移动构造
        HashTable& operator=(const HashTable &other) = delete; // 禁止拷贝赋值
        HashTable& operator=(HashTable&& other) = delete; // 禁止移动赋值

        void insert(const KeyType &k, const ValueType &v) {
            size_t index = hash(k);
            HashNode* curr = table[index];
            while (curr != nullptr) {
                if (curr->key == k) {
                    curr->value = v; //覆盖
                    return;
                }
                curr = curr->next;
            }
            HashNode* newNode = new HashNode(k, v);
            newNode->next = table[index];
            table[index] = newNode;
        }

        void remove(const KeyType &k) {
            size_t index = hash(k);
            if (table[index] == nullptr) {
                return;
            }
            if (table[index]->key == k) {
                HashNode* temp = table[index]->next;
                delete table[index];
                table[index] = temp;
            } else {
                HashNode* curr = table[index];
                while (curr->next != nullptr && curr->next->key != k) {
                    curr = curr->next;
                }
                if (curr->next != nullptr) {
                    HashNode* temp = curr->next->next;
                    delete curr->next;
                    curr->next = temp;
                }
            }
        }

        ValueType* find(const KeyType &k) const {
            size_t index = hash(k);
            HashNode* curr = table[index];
            while (curr != nullptr && curr->key != k) {
                curr = curr->next;
            }
            if (curr != nullptr) {
                return &curr->value;
            }
            return nullptr;
        }
    };
} // yc

#endif //MY_DATA_STRUCTURE_HASHTABLE_H