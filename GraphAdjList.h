//
// Created by yyc08 on 2025/8/29.
//

#ifndef MY_DATA_STRUCTURE_GRAPHADJLIST_H
#define MY_DATA_STRUCTURE_GRAPHADJLIST_H

#include <iostream>
#include <stdexcept>
namespace yc {
    class GraphAdjList {
    private:
        struct EdgeNode {
            int vertex;
            int weight;
            EdgeNode* next;
        };

        struct VertexNode {
            int vertex;
            EdgeNode* head;
        };

        int vertices;
        VertexNode* nodes;

    public:
        GraphAdjList() = default;
        explicit GraphAdjList(size_t n) : vertices(n) {
            nodes = new VertexNode[vertices];
            for (int i = 0; i < vertices; ++i) {
                nodes[i].vertex = i;
                nodes[i].head = nullptr;
            }
        }
        ~GraphAdjList() {
            for (int i = 0; i < vertices; ++i) {
                while (nodes[i].head != nullptr) {
                    EdgeNode* temp = nodes[i].head;
                    nodes[i].head = nodes[i].head->next;
                    delete temp;
                }
            }
            delete[] nodes;
        }

        GraphAdjList(const GraphAdjList &other) = delete; // 禁止拷贝构造
        GraphAdjList(GraphAdjList&& other) = delete; // 禁止移动构造
        GraphAdjList& operator=(const GraphAdjList &other) = delete; // 禁止拷贝赋值
        GraphAdjList& operator=(GraphAdjList&& other) = delete; // 禁止移动赋值

        void add_edge(size_t u, size_t v, const int& w) {
            if (u >= vertices || v >= vertices) {
                throw std::out_of_range("Vertex index out of bounds");
            }
            EdgeNode* newNode = new EdgeNode;
            newNode->vertex = v;
            newNode->weight = w;
            newNode->next = nodes[u].head;
            nodes[u].head = newNode;
        }

        void print_graph() const {
            for (int i = 0; i < vertices; ++i) {
                EdgeNode *current = nodes[i].head;
                std::cout << "Vertex " << i << ": ";
                while (current != nullptr) {
                    std::cout << '(' << current->vertex << ", " << current->weight << ") ";
                    current = current->next;
                }
                std::cout << std::endl;
            }
        }
    };
}


#endif //MY_DATA_STRUCTURE_GRAPHADJLIST_H