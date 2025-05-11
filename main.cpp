#include<iostream>
#include "src/graph.h"


int main() {
    int vertices = 50;
    double density = 0.40; // 40% густина

    AdjacencyListGraph listGraph(vertices);
    listGraph.createGraph(vertices, density);
    std::cout << "Густина списку суміжності: " << listGraph.calculateDensity() << "%\n";

    AdjacencyMatrixGraph matrixGraph(vertices);
    matrixGraph.createGraph(vertices, density);
    std::cout << "Густина матриці суміжності: " << matrixGraph.calculateDensity() << "%\n";

    return 0;
}