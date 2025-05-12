#pragma once
#include "graph.h"

template<typename GraphType>
class DFS {
public:
    void run(const GraphType& graph, int source, vector<bool>& visited) {
        visited[source] = true;

        if constexpr (is_same_v<GraphType, AdjacencyMatrixGraph>) {
            // Логіка для матриці суміжності
            for (int v = 0; v < graph.V; ++v) {
                if (graph.matrix[source][v] != numeric_limits<int>::max() && !visited[v]) {
                    run(graph, v, visited);
                }
            }
        } else {
            // Логіка для списку суміжності
            for (const auto& [v, weight] : graph.list[source]) {
                if (!visited[v]) {
                    run(graph, v, visited);
                }
            }
        }
    }
};