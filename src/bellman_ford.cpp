#include "bellman_ford.h"

template <typename GraphType>
vector<int> BellmanFord<GraphType>::run(const GraphType& graph, int source) {
    vector<int> dist(graph.V, numeric_limits<int>::max());
    dist[source] = 0;

    for (int i = 0; i < graph.V - 1; ++i) {
        for (int u = 0; u < graph.V; ++u) {
            for (const auto& [v, weight] : graph.list[u]) {
                if (dist[u] != numeric_limits<int>::max() && dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                }
            }
        }
    }

    return dist;
}

// Не забудьте включити це в той файл, де буде використовуватися
template class BellmanFord<AdjacencyListGraph>;