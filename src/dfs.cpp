#include "dfs.h"

template <typename GraphType>
void DFS<GraphType>::run(const GraphType& graph, int source, vector<bool>& visited) {
    visited[source] = true;
    for (const auto& [v, weight] : graph.list[source]) {
        if (!visited[v]) {
            run(graph, v, visited);
        }
    }
}

// Не забудьте включити це в той файл, де буде використовуватися
template class DFS<AdjacencyListGraph>;