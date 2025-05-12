#pragma once
#include "graph.h"
#include <vector>
#include <limits>
#include <queue>


template <typename GraphType>
class Dijkstra {
public:
    std::vector<int> run(const GraphType& graph, int source) {
        std::vector<int> dist(graph.V, std::numeric_limits<int>::max());
        dist[source] = 0;
        std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<>> pq;
        pq.push({0, source});

        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();

            if constexpr (std::is_same_v<GraphType, AdjacencyMatrixGraph>) {
                // Обхід матриці суміжності
                for (int v = 0; v < graph.V; ++v) {
                    if (graph.matrix[u][v] != std::numeric_limits<int>::max() && dist[u] + graph.matrix[u][v] < dist[v]) {
                        dist[v] = dist[u] + graph.matrix[u][v];
                        pq.push(std::make_pair(dist[v], v));
                    }
                }
            } else {
                // Обхід списку суміжності
                for (const auto& [v, weight] : graph.list[u]) {
                    if (dist[u] + weight < dist[v]) {
                        dist[v] = dist[u] + weight;
                        pq.push(std::make_pair(dist[v], v));
                    }
                }
            }
        }
        return dist;
    }
};