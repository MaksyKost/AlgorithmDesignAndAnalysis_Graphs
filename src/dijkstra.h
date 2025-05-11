#pragma once
#include "graph.h"
#include <queue>

template <typename GraphType>
class Dijkstra {
public:
    vector<int> run(const GraphType& graph, int source);
};