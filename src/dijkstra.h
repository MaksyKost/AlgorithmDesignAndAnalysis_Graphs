#pragma once
#include "graph.h"
#include <vector>
#include <limits>
#include <queue>


template <typename GraphType>
class Dijkstra {
public:
    vector<int> run(const GraphType& graph, int source);
};