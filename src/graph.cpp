#include "graph.h"

AdjacencyMatrixGraph::AdjacencyMatrixGraph(int vertices) : V(vertices) {
    matrix.resize(V, vector<int>(V, numeric_limits<int>::max()));
}

void AdjacencyMatrixGraph::addEdge(int u, int v, int weight) {
    matrix[u][v] = weight;
}

AdjacencyListGraph::AdjacencyListGraph(int vertices) : V(vertices) {
    list.resize(V);
}

void AdjacencyListGraph::addEdge(int u, int v, int weight) {
    list[u].push_back({v, weight});
}