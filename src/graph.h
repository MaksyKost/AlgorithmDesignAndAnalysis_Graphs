#pragma once
#include <vector>
#include <limits>

using namespace std;

class AdjacencyMatrixGraph {
public:
    int V;
    vector<vector<int>> matrix;

    AdjacencyMatrixGraph(int vertices);
    void addEdge(int u, int v, int weight);
};

class AdjacencyListGraph {
public:
    int V;
    vector<vector<pair<int, int>>> list;

    AdjacencyListGraph(int vertices);
    void addEdge(int u, int v, int weight);
};