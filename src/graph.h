#pragma once
#include <vector>
#include <limits>
#include <set>
#include <cstdlib>



using namespace std;

class AdjacencyMatrixGraph {
public:
    int V;
    vector<vector<int>> matrix;

    AdjacencyMatrixGraph(int vertices);
    void addEdge(int u, int v, int weight);

    void createGraph(int vertices, double density);
    double calculateDensity() const;

    void createGraphWithNegativeWeights(int vertices, double density);
};

class AdjacencyListGraph {
public:
    int V;
    vector<vector<pair<int, int>>> list;

    AdjacencyListGraph(int vertices);
    void addEdge(int u, int v, int weight);

    void createGraph(int vertices, double density);
    double calculateDensity() const;

    void createGraphWithNegativeWeights(int vertices, double density);
};