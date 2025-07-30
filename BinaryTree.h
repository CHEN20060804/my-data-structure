//
// Created by yyc08 on 25-7-24.
//

#ifndef BINARYTREE_H
#define BINARYTREE_H
#include <iostream>
#include <vector>

namespace yc {

    template<typename T>
    class BinaryTree {
    private:
        struct Node {
            T data;
            Node *left;
            Node *right;
            Node() : data(), left(nullptr), right(nullptr) {}
            explicit Node(const T &data) : data(data), left(nullptr), right(nullptr) {}
        };
        Node* root;
        std::vector<Node*> nodes;

        Node* create_tree(size_t id) {
            if (id >= nodes.size()) {
                return nullptr;
            }
            Node* nowNode = nodes[id];
            nowNode->left = create_tree(2 * id + 1);
            nowNode->right = create_tree(2 * id + 2);
            return nowNode;
        }

        void destroy_tree(Node* node) {
            if (node == nullptr) {
                return;
            }
            destroy_tree(node->left);
            destroy_tree(node->right);
            delete node;
        }

        void visit(Node* node) {
            if (node == nullptr) {
                return;
            }
            std::cout << node->data << ' ';
        }

        void pre_order(Node* node) {
            if (node == nullptr) {
                return;
            }
            visit(node);
            pre_order(node->left);
            pre_order(node->right);
        }

        void in_order(Node* node) {
            if (node == nullptr) {
                return;
            }
            in_order(node->left);
            visit(node);
            in_order(node->right);
        }

        void post_order(Node* node) {
            if (node == nullptr) {
                return;
            }
            post_order(node->left);
            post_order(node->right);
            visit(node);
        }
    public:
        BinaryTree() : root(nullptr) {}
        explicit BinaryTree(const std::vector<T> &o_data) : root(nullptr) {
            for (size_t i = 0; i < o_data.size(); ++i) {
                nodes.push_back(new Node(o_data[i]));
            }
            root = create_tree(0);
        }
        BinaryTree(const BinaryTree&) = delete;
        BinaryTree(BinaryTree&&) = delete;
        BinaryTree& operator=(const BinaryTree&) = delete;
        BinaryTree& operator=(BinaryTree&&) = delete;
        ~BinaryTree() {
            destroy_tree(root);
        }

        void create(const std::vector<T> &o_data) {
            destroy_tree(root);
            nodes.clear();
            for (size_t i = 0; i < o_data.size(); ++i) {
                nodes.push_back(new Node(o_data[i]));
            }
            root = create_tree(0);
        }

        void destroy() {
            destroy_tree(root);
            root = nullptr;
            nodes.clear();
        }

        void push_back(const T &data) {
            Node* newNode = new Node(data);
            nodes.push_back(newNode);
            size_t current_id = nodes.size() - 1;
            size_t father_id= (current_id - 1) / 2;
            if (current_id == 0) {
                root = newNode;
                return;
            }
            if (father_id * 2 + 1 == current_id) {
                nodes[father_id]->left = newNode;
            }
            else if (father_id * 2 + 2 == current_id) {
                nodes[father_id]->right = newNode;
            }
        }

        void pop_back() {
            if (nodes.empty()) {
                throw std::invalid_argument("Empty Tree");
            }

            size_t last_id = nodes.size() - 1;
            Node* lastNode = nodes.back();

            if (nodes.size() == 1) {
                delete lastNode;
                nodes.pop_back();
                root = nullptr;
                return;
            }
            size_t father_id = (last_id - 1) / 2;
            Node* parent = nodes[father_id];

            if (father_id * 2 + 1 == last_id) {
                parent->left = nullptr;
            } else if (father_id * 2 + 2 == last_id) {
                parent->right = nullptr;
            }

            // 删除节点，弹出数组
            delete lastNode;
            nodes.pop_back();
        }

        void print_in_preorder() {
            pre_order(root);
            std::cout << std::endl;
        }

        void print_in_inorder() {
            in_order(root);
            std::cout << std::endl;
        }

        void print_in_postorder() {
            post_order(root);
            std::cout << std::endl;
        }

        void print_in_levelorder() {
            for (auto& node : nodes) {
                std::cout << node->data << ' ';
            }
            std::cout << std::endl;
        }
};

} // yc

#endif //BINARYTREE_H
