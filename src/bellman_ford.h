#pragma once
#include "graph.h"
#include <vector>
#include <limits>
#include <type_traits> // Для is_same_v

template <typename GraphType>
class BellmanFord {
public:
    std::vector<int> run(const GraphType& graph, int source) {
        std::vector<int> dist(graph.V, std::numeric_limits<int>::max());
        dist[source] = 0;

        // Główna pętla Bellmana-Forda
        for (int i = 0; i < graph.V - 1; ++i) {
            for (int u = 0; u < graph.V; ++u) {
                if constexpr (std::is_same_v<GraphType, AdjacencyMatrixGraph>) {
                    for (int v = 0; v < graph.V; ++v) {
                        if (graph.matrix[u][v] != std::numeric_limits<int>::max() && 
                            dist[u] != std::numeric_limits<int>::max() && 
                            dist[u] + graph.matrix[u][v] < dist[v]) {
                            dist[v] = dist[u] + graph.matrix[u][v];
                        }
                    }
                } else {
                    for (const auto& [v, weight] : graph.list[u]) {
                        if (dist[u] != std::numeric_limits<int>::max() && 
                            dist[u] + weight < dist[v]) {
                            dist[v] = dist[u] + weight;
                        }
                    }
                }
            }
        }

        // Wykrywanie ujemnych cykli
        for (int u = 0; u < graph.V; ++u) {
            if constexpr (std::is_same_v<GraphType, AdjacencyMatrixGraph>) {
                for (int v = 0; v < graph.V; ++v) {
                    if (graph.matrix[u][v] != std::numeric_limits<int>::max() && 
                        dist[u] != std::numeric_limits<int>::max() && 
                        dist[u] + graph.matrix[u][v] < dist[v]) {
                        return {}; // Zwracamy pusty wektor, aby zaznaczyć problem
                    }
                }
            } else {
                for (const auto& [v, weight] : graph.list[u]) {
                    if (dist[u] != std::numeric_limits<int>::max() && 
                        dist[u] + weight < dist[v]) {
                        return {}; // Zwracamy pusty wektor
                    }
                }
            }
        }

        return dist;
    }
};