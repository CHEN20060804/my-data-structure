//
// Created by yyc08 on 25-7-30.
//

#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H
#include <iostream>

namespace yc {

    template<typename T>
    class BinarySearchTree {
    private:
        struct Node {
            T data;
            Node *left;
            Node *right;
            Node() : data(), left(nullptr), right(nullptr) {}
            explicit Node(const T &data) : data(data), left(nullptr), right(nullptr) {}
        };
        Node* root;

        Node* insertNode(Node* node, const T& value) {
            if (node == nullptr) {
                return new Node(value);
            }
            if (value < node->data) {
                node->left = insertNode(node->left, value);
            } else if (value > node->data) {
                node->right = insertNode(node->right, value);
            }
            return node;
        }

        bool searchNode(Node* node, const T& value) {
            if (node == nullptr) {
                return false;
            }
            if (value < node->data) {
                return searchNode(node->left, value);
            }
            if (value > node->data) {
                return searchNode(node->right, value);
            }
            return true;
        }

        Node* removeNode(Node* node, const T& value) {
            if (node == nullptr) {
                return nullptr;
            }
            if (value < node->data) {
                node->left = removeNode(node->left, value);
            } else if (value > node->data) {
                node->right = removeNode(node->right, value);
            } else {
                if (node->left == nullptr && node->right == nullptr) {
                    delete node;
                    return nullptr;
                } else if (node->left == nullptr) {
                    Node* temp = node->right;
                    delete node;
                    return temp;
                } else if (node->right == nullptr) {
                    Node* temp = node->left;
                    delete node;
                    return temp;
                } else {
                    Node* temp = node->right;
                    while (temp->left != nullptr) {
                        temp = temp->left;
                    }
                    node->data = temp->data;
                    node->right = removeNode(node->right, temp->data);
                }
            }
            return node;
        }

        void destroy_tree(Node* node) {
            if (node == nullptr) {
                return;
            }
            destroy_tree(node->left);
            destroy_tree(node->right);
            delete node;
        }

        void in_order(Node* node) {
            if (node == nullptr) {
                return;
            }
            in_order(node->left);
            std::cout << node->data << " ";
            in_order(node->right);
        }

    public:
        BinarySearchTree() : root(nullptr) {}

        ~BinarySearchTree() {
            destroy_tree(root);
        }

        void insert(const T& value) {
            root = insertNode(root, value);
        }

        bool search(const T& value) {
            return searchNode(root, value);
        }

        void remove(const T& value) {
            root = removeNode(root, value);
        }

        void destroy() {
            destroy_tree(root);
            root = nullptr;
        }

        void print_in_order() {
            in_order(root);
            std::cout << std::endl;
        }
};

} // yc

#endif //BINARYSEARCHTREE_H
