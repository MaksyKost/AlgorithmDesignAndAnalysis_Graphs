#pragma once
#include "graph.h"

template <typename GraphType>
class DFS {
public:
    void run(const GraphType& graph, int source, vector<bool>& visited);
};