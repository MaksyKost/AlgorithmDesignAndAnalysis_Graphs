#include "dijkstra.h"

template <typename GraphType>
vector<int> Dijkstra<GraphType>::run(const GraphType& graph, int source) {
    vector<int> dist(graph.V, numeric_limits<int>::max());
    dist[source] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    pq.push({0, source});

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        for (const auto& [v, weight] : graph.list[u]) {
            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }

    return dist;
}

// Не забудьте включити це в той файл, де буде використовуватися
template class Dijkstra<AdjacencyListGraph>;