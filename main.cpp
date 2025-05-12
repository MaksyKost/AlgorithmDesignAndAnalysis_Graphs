#include<iostream>
#include <vector>
#include "src/graph.h"
#include "src/bellman_ford.h"


int main() {
    int size = 50;
    double density = 0.4; // 40% густина
    vector<bool> visited(size, false);

    AdjacencyListGraph listGraph(size);
    listGraph.createGraph(size, density);

    AdjacencyMatrixGraph matrixGraph(size);
    matrixGraph.createGraph(size, density);

    BellmanFord<AdjacencyListGraph> bellman_list;
    BellmanFord<AdjacencyMatrixGraph> bellman_matrix;


    bellman_list.run(listGraph, 0);
    bellman_matrix.run(matrixGraph, 0);
    
    std::cout << listGraph.calculateDensity();

    return 0;
}