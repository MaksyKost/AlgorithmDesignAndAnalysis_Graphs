#include "graph.h"



AdjacencyMatrixGraph::AdjacencyMatrixGraph(int vertices) : V(vertices) {
    matrix.resize(V, vector<int>(V, numeric_limits<int>::max()));
}

void AdjacencyMatrixGraph::addEdge(int u, int v, int weight) {
    matrix[u][v] = weight;
}

void AdjacencyListGraph::createGraph(int vertices, double density) {
    V = vertices;
    list.clear();
    list.resize(V);

    int maxEdges = V * (V - 1); // Орієнтований граф
    int targetEdges = static_cast<int>(density * maxEdges);

    std::set<std::pair<int, int>> addedEdges;
    srand(123);

    while (addedEdges.size() < targetEdges) {
        int u = rand() % V;
        int v = rand() % V;
        int weight = rand() % 100 + 1;

        if (u != v && addedEdges.find({u, v}) == addedEdges.end()) {
            addEdge(u, v, weight);
            addedEdges.insert({u, v});
        }
    }
}


AdjacencyListGraph::AdjacencyListGraph(int vertices) : V(vertices) {
    list.resize(V);
}

void AdjacencyListGraph::addEdge(int u, int v, int weight) {
    list[u].push_back({v, weight});
}


void AdjacencyMatrixGraph::createGraph(int vertices, double density) {
    V = vertices;
    matrix.clear();
    matrix.resize(V, std::vector<int>(V, numeric_limits<int>::max()));

    int maxEdges = V * (V - 1);
    int targetEdges = static_cast<int>(density * maxEdges);

    int edgesAdded = 0;
    srand(123);

    while (edgesAdded < targetEdges) {
        int u = rand() % V;
        int v = rand() % V;
        int weight = rand() % 100 + 1;

        if (u != v && matrix[u][v] == numeric_limits<int>::max()) {
            matrix[u][v] = weight;
            edgesAdded++;
        }
    }

}

double AdjacencyListGraph::calculateDensity() const {
    int maxEdges = V * (V - 1); // Максимальна кількість ребер у орієнтованому графі
    int actualEdges = 0;

    for (const auto& adj : list) {
        actualEdges += adj.size();
    }

    return (static_cast<double>(actualEdges) / maxEdges) * 100.0; // Густина у %
}

double AdjacencyMatrixGraph::calculateDensity() const {
    int maxEdges = V * (V - 1); // Максимальна кількість ребер у орієнтованому графі
    int actualEdges = 0;

    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            if (matrix[i][j] != std::numeric_limits<int>::max()) { // Перевірка на наявність ребра
                actualEdges++;
            }
        }
    }

    return (static_cast<double>(actualEdges) / maxEdges) * 100.0; // Густина у %
}