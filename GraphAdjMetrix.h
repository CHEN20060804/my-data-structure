//
// Created by yyc08 on 25-8-5.
//

#ifndef GRAPHADJMETRIX_H
#define GRAPHADJMETRIX_H
#include <iostream>
#include <stdexcept>

namespace yc {

class GraphAdjMatrix {
private:
    size_t vertices;
    int** adjMatrix;
    static constexpr int INF = -1;

public:
    explicit GraphAdjMatrix(size_t vertices) : vertices(vertices) {
        adjMatrix = new int*[vertices];
        for (int i = 0; i < vertices; i++) {
            adjMatrix[i] = new int[vertices];
            for (int j = 0; j < vertices; j++) {
                adjMatrix[i][j] = INF;
            }
        }
    }
    ~GraphAdjMatrix() {
        for (int i = 0; i < vertices; i++) {
            delete[] adjMatrix[i];
        }
        delete[] adjMatrix;
    }

    GraphAdjMatrix(const GraphAdjMatrix &other) = delete; // 禁止拷贝构造
    GraphAdjMatrix(GraphAdjMatrix&& other) = delete; // 禁止移动构造
    GraphAdjMatrix& operator=(const GraphAdjMatrix &other) = delete; // 禁止拷贝赋值
    GraphAdjMatrix& operator=(GraphAdjMatrix&& other) = delete; // 禁止移动赋值

    void add_edge(size_t src, size_t dest, int weight) {
        if (src >= vertices || dest >= vertices) {
            throw std::out_of_range("Vertex index out of bounds");
        }
        adjMatrix[src][dest] = weight;
    }

    void remove_edge(size_t src, size_t dest) {
        if (src >= vertices || dest >= vertices) {
            throw std::out_of_range("Vertex index out of bounds");
        }
        adjMatrix[src][dest] = INF;
    }

    void print_graph() const {
        for (int i = 0; i < vertices; i++) {
            for (int j = 0; j < vertices; j++) {
                std::cout << adjMatrix[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

};

} // yc

#endif //GRAPHADJMETRIX_H
